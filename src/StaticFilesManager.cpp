#include "StaticFilesManager.hpp"

#include <filesystem>
#include <mime/mime.types.hxx>
#include <pre/file/string.hpp> 

#include <cstring>
#include <stdarg.h>

oatpp::String StaticFilesManager::getFile(const oatpp::String& path) {
  if(!path) {
    return nullptr;
  }
  oatpp::String filename = m_basePath + "/" + path;
  std::error_condition ec;
  auto file_content = pre::file::to_string(filename->c_str(), ec);
  oatpp::String file = file_content.data();
  return (ec) ? nullptr : file;
}

oatpp::String StaticFilesManager::guessMimeType(const oatpp::String& filename) {
  oatpp::String content_type = "application/octet-stream";
  auto extension = std::filesystem::path(filename->c_str()).extension();
  OATPP_LOGD("StaticFilesManager::guessMimeType", "extension %s", extension.c_str());

  if (mime::mime_types.find(extension.generic_string()) != mime::mime_types.end()) {
    content_type = mime::mime_types.at(extension.generic_string());
  }

  return content_type;
}
