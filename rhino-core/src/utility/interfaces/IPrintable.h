#pragma once

#include <string>

namespace rhino {

	class IPrintable {

		public:
			
			virtual std::string toString() const = 0;

			inline friend std::ostream& operator<<(std::ostream& stream, const IPrintable& p) {
				stream << p.toString();
				return stream;
			}

	};

}
