#pragma once

namespace util {

	inline uint lon2tilex(double lon, int z) {
		lon = std::max(std::min(lon, 179.8), -179.8);

		int x = (int)(floor((lon + 180.0) / 360.0 * pow(2.0, z)));
                return x & ((1 << z) - 1);
	}

	inline uint lat2tiley(double lat, int z) {
		lat = std::max(std::min(lat, 89.8), -89.8);

		int y = (int)(floor((1.0 - log(tan(lat * M_PI / 180.0) + 1.0 / cos(lat * M_PI / 180.0)) / M_PI) / 2.0 * pow(2.0, z)));
                return y & ((1 << z) - 1);
	}
	

	inline double tilex2lon(double x, int z) {
		return x / pow(2.0, z) * 360.0 - 180;
	}

	inline double tiley2lat(double y, int z) {
		double n = M_PI - 2.0 * M_PI * y / pow(2.0, z);
		return 180.0 / M_PI * atan(0.5 * (exp(n) - exp(-n)));
	}

}
