#include "block_chain.h"
#include "sha256.h"
#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>
#include <memory>
#include <future>
#include <string>
#include <atomic>
#include <mutex>

using namespace std;
using namespace std::chrono;
using std::string;

block::block(uint32_t index, const string &data)
	: _index(index), _data(data), _nonce(), _time(static_cast<long>(index))
{
}

// Get the number of supported threads
auto num_threads = thread::hardware_concurrency();

void block::mine_hash(uint32_t difficulty, uint64_t nonce, std::promise<std::string> * p_hash, std::shared_ptr<std::atomic_bool> found)
{
	// Used for comparing hash
	string str(difficulty, '0');

	// Used so each thread can calculate their own hash (independantly)
	string t_hash;

	for (int i = 0; !*found; i += num_threads)
	{
		// If the current hash is correct
		if (t_hash.substr(0, difficulty) == str)
		{
			// Set Found to True and Pass the Value (hash)
			(*found) = true;
			(*p_hash).set_value(t_hash);
		}
		else
		{
			// Increment Nonce and re-calc hash.
			++_nonce;
			t_hash = calculate_hash(_nonce);
		}
	}
}

void block::mine_block(uint32_t difficulty) noexcept
{
	// Creating a Promise/Future to get the correct Hash value from the mine_hash function.
	promise<string> p_hash;
	future<string> f_hash = p_hash.get_future();

	// Creation of Vector for threads
	vector<thread> threads;

	// Creating the Atomic Bool and setting it to False
	auto found = make_shared<atomic_bool>(false);

	// Starts timer
	auto start = system_clock::now();

	// For loop to start n threads
	for (size_t i = 0; i < num_threads; ++i)
	{
		threads.push_back(thread(&block::mine_hash, this, difficulty, 0, &p_hash, found));
	}

	// Join all the threads
	for (auto &t : threads)
	{
		t.join();
	}

	// Ends timer
	auto end = system_clock::now();

	// Works out duration
	duration<double> diff = end - start;

	// Gets the future value for the hash
	_hash = f_hash.get();

	cout << "Block mined: " << _hash << " in " << diff.count() << " seconds " << "using " << num_threads << " Thread/s " << endl;
}

std::string block::calculate_hash(uint64_t nonce) const noexcept
{
	stringstream ss;
	ss << _index << _time << _data << nonce << prev_hash;
	return sha256(ss.str());
}

block_chain::block_chain()
{
	_chain.emplace_back(block(0, "Genesis Block"));
	_difficulty = 6;
}

void block_chain::add_block(block &&new_block) noexcept
{
	new_block.prev_hash = get_last_block().get_hash();
	new_block.mine_block(_difficulty);
	_chain.push_back(new_block);
}
