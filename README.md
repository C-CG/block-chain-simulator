# Blockchain Simulator

In this project directory you will find a c++ application that displays CPU-based Concurrency and Parallelism within a Blockchain Simulator that uses the **SHA-256** algorithm for hashing.

# The Task

The aim of this coursework dealt with improving the performance of a blockchain simulator via parallel techniques such as OpenMP, algorithmic skeletons or my chosen implementation **multi-threading**.

# Introduction to Blockchain

Blockchain is a current technology that is trying to solve the problem with sending money digitally. Currently, transactions can take days to process along with a fee, this is where Blockchain comes in. Blockchain allows for transactions to be sent and received instantly with transactions being able to be tracked by anyone via a **"public ledger"** to look for false transactions.

The steps of how a Blockchain Simulator would work are as followed:

- The **Difficulty** of the Blockchain is established.
- An Initial Block (Genesis Block) is added to the chain and its content is hashed.
- When another Block is added to the chain it points back to the previous Block's hash in-order to check for any unauthorised changes, but before that is must be **"signed"**.
- In-order for a Block to be signed (hash starts with the correct number of 0's, established via the **Difficulty**) a new value must be created (**"Nonce"**).
- The Nonce allows for the hash of the Block to be changed without the data being affected, this random value is incremented and the Block re-hashed until it is regarded as **signed**.
- Once the Block has been signed, it can successfully be added to the chain.

# Implementation

# Results

# Conclusions
