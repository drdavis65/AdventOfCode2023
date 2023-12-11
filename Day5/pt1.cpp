#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

enum class ParsingState {
  None,
  seed_soil,
  soil_fert,
  fert_water,
  water_light,
  light_temp,
  temp_humidity,
  humidity_location
};

int main() {
  std::ifstream file("text.txt");
  if (!file.is_open()) {
    std::cerr << "Failed to open file." << std::endl;
    return 1;
  }
  std::string line;

  std::vector<long long> seeds;
  std::vector<std::array<long long, 3>> seed_soil;
  std::vector<std::array<long long, 3>> soil_fert;
  std::vector<std::array<long long, 3>> fert_water;
  std::vector<std::array<long long, 3>> water_light;
  std::vector<std::array<long long, 3>> light_temp;
  std::vector<std::array<long long, 3>> temp_humidity;
  std::vector<std::array<long long, 3>> humidity_location;
  long long dest, src, range;
  ParsingState state = ParsingState::None;

  while (getline(file, line)) {
    std::cout << "Reading line: " << line << std::endl;
    if (line.empty()) {
      std::cout << "Encountered blank line. Resetting state." << std::endl;
      state = ParsingState::None;
      continue;
    }

    std::istringstream iss(line);
    if (state == ParsingState::None) {
      std::string key;
      iss >> key;
      std::cout << "Detected key: " << key << std::endl;

      if (key == "seeds:") {
        state = ParsingState::None; // No state change needed for seeds
        long long seed;
        while (iss >> seed) {
          seeds.push_back(seed);
        }
      } else if (key == "seed-to-soil") {
        state = ParsingState::seed_soil;
      } else if (key == "soil-to-fertilizer") {
        state = ParsingState::soil_fert;
      } else if (key == "fertilizer-to-water") {
        state = ParsingState::fert_water;
      } else if (key == "water-to-light") {
        state = ParsingState::water_light;
      } else if (key == "light-to-temperature") {
        state = ParsingState::light_temp;
      } else if (key == "temperature-to-humidity") {
        state = ParsingState::temp_humidity;
      } else if (key == "humidity-to-location") {
        state = ParsingState::humidity_location;
      }
    } else if (state == ParsingState::seed_soil) {
      iss >> dest >> src >> range;
      std::cout << "SeedSoil mapping: " << dest << " " << src << " " << range
                << std::endl;
      seed_soil.push_back({dest, src, range});
    } else if (state == ParsingState::soil_fert) {
      iss >> dest >> src >> range;
      std::cout << "SoilFert mapping: " << dest << " " << src << " " << range
                << std::endl;
      soil_fert.push_back({dest, src, range});
    } else if (state == ParsingState::fert_water) {
      iss >> dest >> src >> range;
      std::cout << "FertWater mapping: " << dest << " " << src << " " << range
                << std::endl;
      fert_water.push_back({dest, src, range});
    } else if (state == ParsingState::water_light) {
      iss >> dest >> src >> range;
      std::cout << "WaterLight mapping: " << dest << " " << src << " " << range
                << std::endl;
      water_light.push_back({dest, src, range});
    } else if (state == ParsingState::light_temp) {
      iss >> dest >> src >> range;
      std::cout << "LightTemp mapping: " << dest << " " << src << " " << range
                << std::endl;
      light_temp.push_back({dest, src, range});
    } else if (state == ParsingState::temp_humidity) {
      iss >> dest >> src >> range;
      std::cout << "TempHumid mapping: " << dest << " " << src << " " << range
                << std::endl;
      temp_humidity.push_back({dest, src, range});
    } else if (state == ParsingState::humidity_location) {
      iss >> dest >> src >> range;
      std::cout << "HumidityLocation mapping: " << dest << " " << src << " "
                << range << std::endl;
      humidity_location.push_back({dest, src, range});
    }
  }

  std::vector<long long> locations;
  for (const auto &seed : seeds) {
    long long soil;
    for (auto &s : seed_soil) {
      if (seed >= s[1] && seed < s[1] + s[2])
        soil = s[0] + (seed - s[1]);
    }
    long long fert;
    for (auto &s : soil_fert) {
      if (soil >= s[1] && soil < s[1] + s[2])
        fert = s[0] + (soil - s[1]);
    }
    long long water;
    for (auto &s : fert_water) {
      if (fert >= s[1] && fert < s[1] + s[2])
        water = s[0] + (fert - s[1]);
    }
    long long light;
    for (auto &s : water_light) {
      if (water >= s[1] && water < s[1] + s[2])
        light = s[0] + (water - s[1]);
    }
    long long temp;
    for (auto &s : light_temp) {
      if (light >= s[1] && light < s[1] + s[2])
        temp = s[0] + (light - s[1]);
    }
    long long humid;
    for (auto &s : temp_humidity) {
      if (temp >= s[1] && temp < s[1] + s[2])
        humid = s[0] + (temp - s[1]);
    }
    long long location;
    for (auto &s : humidity_location) {
      if (humid >= s[1] && humid < s[1] + s[2])
        location = s[0] + (humid - s[1]);
    }
    locations.push_back(location);
  }
  std::sort(locations.begin(), locations.end());
  std::cout << "Min location: " << locations[0] << std::endl;
}
