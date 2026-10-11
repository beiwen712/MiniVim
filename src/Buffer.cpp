#include <fstream>

#include "Buffer.hpp"

namespace sjtu {

Buffer::Buffer(const std::filesystem::path& path){
    path_=path;
    modified = false;
    if(path.empty()) {
       lines_.push_back("");
        return;
    }
    std::ifstream file(path);
    if(!file) {
        throw std::runtime_error("Failed to open file: " + path.string());
    }
    std::string line;

    while(std::getline(file, line)) {
        lines_.push_back(std::move(line));
        line.clear();
    }
    if(file.bad()) {
        throw std::runtime_error("Failed to read file:" + path.string());
    }
    if(lines_.empty()) {
        lines_.push_back("");
    }
    // throw std::runtime_error("Not implemented.");
    //从path指向的文件构造Buffer,你需要打开文件并且把文件内容填充进Buffer,并正确初始化一些状态.
    //注意path可能为空的边界情况
}

Buffer::Buffer(std::vector<std::string> lines, std::filesystem::path path) {
    if(lines_.empty()) 
        lines_.push_back("");
    modified = false;
    // throw std::runtime_error("Not implemented.");
}

std::size_t Buffer::GetLineCount() const {
    //返回文件行数
    return lines_.size();
    // throw std::runtime_error("Not implemented.");
}

const std::string& Buffer::GetLineAt(std::size_t row) const {
    //返回第row行的内容
    return lines_[row];
    // throw std::runtime_error("Not implemented.");
}


std::string Buffer::GetDisplayName() const {
    //返回文件名,若是新文件,返回"[No Name]"
    if(path_.empty()) 
        return "[No Name]";
    return path_.filename().string();
    // throw std::runtime_error("Not implemented.");
}

bool Buffer::IsModified() const {
    //返回文件和上次保存比起来是否被修改过
    return modified;
    // throw std::runtime_error("Not implemented.");
}
// 111 未实现

void Buffer::InsertCharacter(std::size_t row, std::size_t column, char value) {
    //在第row行第col列插入一个value, 注意越界检查
    if(row >= lines_.size()) return ;
    if(column > lines_[row].size()) return ;
    lines_[row].insert(lines_[row].begin() + static_cast<std::ptrdiff_t>(column), value);
    //static_cast<std::ptrdiff_t>
    modified = true;
//    throw std::runtime_error("Not implemented.");
}

void Buffer::EraseCharacter(std::size_t row, std::size_t column) {
   //在第row行第col列删除一个value
   if(row >= lines_.size()) return ;
   if(column > lines_[row].size()) return ;

    lines_[row].erase(lines_[row].begin() + static_cast<ptrdiff_t>(column));
    modified = true;
//    throw std::runtime_error("Not implemented.");
}

void Buffer::SplitLine(std::size_t row, std::size_t column) {
    //在第row行第col列分割,即在此处敲了回车键
    if(row >= lines_.size()) return;
    if(column > lines_[row].size()) return;

    std::string& line = lines_[row];
    std::string tail = line.substr(column);
    line.erase(column);
    lines_.insert(lines_.begin() + static_cast<std::ptrdiff_t>(row) + 1, std::move(tail));
    modified = true;
    // throw std::runtime_error("Not implemented.");
}

void Buffer::JoinLine(std::size_t row) {
   //把第row + 1行合并进第row行
   if(row + 1 >=lines_.size()) return ;
   std::string line = lines_[row + 1];
   lines_.erase(lines_.begin() + static_cast<ptrdiff_t>(row) + 1);
   lines_[row].append(line);
   modified = true;
//    throw std::runtime_error("Not implemented.");
}

void Buffer::Save() {
   //把文件内容保存, 直接调用WriteTo方法
    if(path_.empty()) {
        throw std::runtime_error("No file name.");
    }
    WriteTo(path_);
    modified = false;
   //    throw std::runtime_error("Not implemented.");
}

void Buffer::SaveAs(const std::filesystem::path& path) {
    if(path.empty()) {
        throw std::runtime_error("No file name.");
    }
    WriteTo(path);
    path_ = path;
    modified = false;
//   throw std::runtime_error("Not implemented.");
}


void Buffer::WriteTo(const std::filesystem::path& path) const {
   //实际将缓冲区中的内容写入path指向的文件中
    std::ofstream file(path);
    if(!file) {
        throw std::runtime_error("Failed to open file for writing: " + path.string());
    }
    if(lines_.size() == 1 && lines_[0].empty()) {
        return;
    }
    for(const auto &line : lines_) {
        file << line << "\n";
    }
  /*for(const std::size_t row = 0; row < lines_.size(); row++) {
        file << lines_[row];
        if(row + 1 < lines_.size()) 
            file << "\n";
    }*/
//    throw std::runtime_error("Not implemented.");
}

} // namespace sjtu
