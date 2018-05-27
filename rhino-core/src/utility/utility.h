#pragma once 

#include <vector>
#include <iterator>
#include <string>

namespace rhino {

	struct Utility {

		private:
			template<typename Out>
			static void split(const std::string &s, char delim, Out result) {
				std::stringstream ss(s);
				std::string item;
				while (std::getline(ss, item, delim)) {
					*(result++) = item;
				}
			}

		public:
			static std::vector<std::string> split(const std::string &s, char delim) {
				std::vector<std::string> elems;
				split(s, delim, std::back_inserter(elems));
				return elems;
			}

			static std::string removeSpaces(const std::string& str) {
				std::string stm = str;
				while (stm[0] == *" ") {
					stm = stm.substr(1);
				}
				return stm;
			}

			template<typename DEST, typename SRC>
			static DEST punnData(const SRC& value) {
				return *((DEST*)&value);
			}

			template<typename DEST>
			static DEST punnData(void* value) {
				return *((DEST*)value);
			}

	};

}