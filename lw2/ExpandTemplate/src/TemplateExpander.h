#pragma once

#include <map>
#include <string>
#include <unordered_map>

typedef std::unordered_map<std::string, std::string> TemplateParams;

std::string ExpandTemplate(const std::string& templateString, const TemplateParams& params);