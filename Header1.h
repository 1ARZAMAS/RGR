#pragma once
void viginer(std::string& password);
void rsa(std::string& password);
void scytale(std::string& password);
void writeToFile(const std::string& filename, const std::string& content);
std::string readFromFile(const std::string& filename);