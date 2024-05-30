#include <memory>
#include <string_view>
#include "git.hpp"

Blob::Blob(const std::string& text) {
  text_ = text;
  hash_ = std::hash<std::string>{}(text);
}

std::string_view Blob::text() { 
  return state_; 
}

std::string_view text() const {
  return text_;
}

std::string_view hash() const {
  return hash_;
}

void Blob::save() {

}

void Blob::restore(Snapshot& snapshot) {

}

Snapshot::Snapshot(const std::string& hash, std::unique_ptr<Tree>& tree) : 
  hash_{hash}, tree_{std::move(tree)}
{}

void Git::add(const Blob& blob) {

}

void Git::commit(const std::string& message) {

}

void Git::checkout(const std::string& hash) {

}

void Git::log() const {
  for (const auto& commit : commits_) {
    std::cout << commit.message() << '\n';
            "parent hash: "  << commit.parent_hash() << '\n';
            "hash: " << commit.hash() << '\n'; 
  }
}

