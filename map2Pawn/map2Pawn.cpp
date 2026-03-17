#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::string getAttributeValue(const std::string& line, const std::string& attribute) {
    std::string searchStr = attribute + "=\"";
    size_t startPos = line.find(searchStr);
    if (startPos == std::string::npos) return "";

    startPos += searchStr.length();
    size_t endPos = line.find("\"", startPos);
    if (endPos == std::string::npos) return "";

    return line.substr(startPos, endPos - startPos);
}

int main(int argc, char* argv[]) {
    std::string line;
    int count = 0;

	std::cout << "MtaMapToPawn - Konwerter mapy z mta do formatu Pawn\n";
	std::cout << "Narzedzie do konwersji obiektow z pliku mapy MTA do funkcji RemoveBuildingForPlayer\n";
    std::cout << "Autor: MisterMagik\n";
    std::cout << "Wykonano dla Old School RolePlay\n";
    if (argc < 2) {
        std::cerr << "Blad: Podaj nazwe pliku mapy jako argument.\n";
        std::cerr << "Uzycie: " << argv[0] << " plik.map\n";
        return 1;
	}
    
    std::string inputFileName = argv[1];
    std::string outputFileName = argv[1];
    outputFileName += ".pwn";

	std::cerr << "Wczytywanie pliku: " << outputFileName << std::endl;
    return 0;
    std::ifstream inputFile(inputFileName);
    std::ofstream outputFile(outputFileName);

    if (!inputFile.is_open()) {
        std::cerr << "Blad: Nie mozna otworzyc pliku " << inputFileName << std::endl;
        return 1;
    }

    if (!outputFile.is_open()) {
        std::cerr << "Blad: Nie mozna utworzyc pliku " << outputFileName << std::endl;
        return 1;
    }

   

    // Naglowek w pliku wyjsciowym
    outputFile << "// Wygenerowane RemoveBuildingForPlayer z pliku " << inputFileName << "\n";

    while (std::getline(inputFile, line)) {
        // Szukamy tylko linii zawierajacych removeWorldObject
        if (line.find("<removeWorldObject") != std::string::npos) {
            std::string model = getAttributeValue(line, "model");
            std::string radius = getAttributeValue(line, "radius");
            std::string posX = getAttributeValue(line, "posX");
            std::string posY = getAttributeValue(line, "posY");
            std::string posZ = getAttributeValue(line, "posZ");

            // Jesli udalo sie znalezc wszystkie potrzebne dane
            if (!model.empty() && !radius.empty() && !posX.empty() && !posY.empty() && !posZ.empty()) {
                outputFile << "RemoveBuildingForPlayer(playerid, "
                    << model << ", "
                    << posX << ", "
                    << posY << ", "
                    << posZ << ", "
                    << radius << ");\n";
                count++;
            }
        }
    }

    inputFile.close();
    outputFile.close();

    std::cout << "Zakonczono sukcesem! Przetworzono " << count << " obiektow." << std::endl;
    std::getchar();

    return 0;
}