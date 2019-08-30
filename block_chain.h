#pragma once

#include <string>
#include <vector>
#include <future>
#include <atomic>

class block
{
private:
	// The index of the block in the chain.
	uint32_t _index;
	// A modifier used to get a suitable block.
	uint64_t _nonce;
	// Data stored in the block.
	std::string _data;
	// Hash code of this block.
	std::string _hash;
	// Time code block was created.
	long _time;


public:
	block(uint32_t index, const std::string &data);

	void mine_block(uint32_t difficulty) noexcept;

	// New Function to create and calculate new hashes in Parallel
	void mine_hash(uint32_t, uint64_t, std::promise<std::string> *, std::shared_ptr<std::atomic_bool> found);

	inline const std::string& get_hash() const noexcept { return _hash; }

	// Moved the function from Private to Public so other functions can access it
	std::string calculate_hash(uint64_t) const noexcept;

	// Hash code of the previous block in the chain.
	std::string prev_hash;
};

class block_chain
{
private:
	uint32_t _difficulty;
	std::vector<block> _chain;
	inline const block& get_last_block() const noexcept { return _chain.back(); }

public:
	block_chain();
	void add_block(block &&new_block) noexcept;
};