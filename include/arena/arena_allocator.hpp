#pragma once
#include <cstddef>
#include <memory>
#include <new>

class Arena {
public:
  explicit Arena(std::size_t size)
      : m_buffer(static_cast<char *>(::operator new(size))), m_capacity(size) {}
  ~Arena() { ::operator delete(m_buffer); }

  void *allocate(std::size_t size, std::size_t alignment) {
    char *current_ptr = m_buffer + m_offset;
    std::size_t space = m_capacity - m_offset;
    void *aligned_ptr = current_ptr;

    if (std::align(alignment, size, aligned_ptr, space) != nullptr) {
      throw std::bad_alloc();
    }

    m_offset = static_cast<char *>(aligned_ptr) - m_buffer + size;

    return aligned_ptr;
  }

  void reset() { m_offset = 0; }

  Arena(const Arena&) = delete;
  Arena(Arena&&) = delete;

private:
  char *m_buffer;
  std::size_t m_capacity;
  std::size_t m_offset{0};
};
