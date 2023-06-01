#pragma once

// When chunk is free 'next' contains pointer to a next free chunk
// When it's allocated, this space is used by user
struct Chunk {
  Chunk *next;
};

class PoolAllocator {
 public:
  PoolAllocator(size_t chunksPerBlock) : chunksPerBlock_(chunksPerBlock), alloc_(nullptr) {}

  void *allocate(size_t size) {
    if (alloc_ == nullptr) {
      alloc_ = allocateBlock(size);
    }
    Chunk *free_chunk = alloc_;
    alloc_ = alloc_->next;
    return free_chunk;
  }

  void deallocate(void *chunk, size_t size) {
    auto temp = reinterpret_cast<Chunk *>(chunk);
    temp->next = alloc_;
    alloc_ = temp;
  }

 private:
  size_t chunksPerBlock_;
  Chunk *alloc_;

 private:
  Chunk *allocateBlock(size_t chunkSize) {
    Chunk *block_begin = reinterpret_cast<Chunk *>(malloc(chunksPerBlock_ * chunkSize));
    auto *curr_chunk = block_begin;
    for (size_t i = 0; i < chunksPerBlock_ - 1; ++i) {
      curr_chunk->next = reinterpret_cast<Chunk *>(reinterpret_cast<char *>(curr_chunk) + chunkSize);
      curr_chunk = curr_chunk->next;
    }
    curr_chunk->next = nullptr;
    return block_begin;
  }
};
