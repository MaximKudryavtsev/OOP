#include "stdafx.h";

using namespace std;

struct BmpFileHeader
{
	WORD fileType;
	DWORD fileSize;
};

struct BmpInfoHeader
{
	DWORD imageWidth;
	DWORD imageHeight;
	WORD bitsPerPixel;
	DWORD compressionType;
};

bool OpenBinaryFileForReading(ifstream &file, const string &fileName)
{
	file.open(fileName, ifstream::binary);
	return file.is_open();
}

void ReadBmpFileHeader(ifstream &file, BmpFileHeader &fileHeader)
{
	file.read(reinterpret_cast<char*>(&fileHeader.fileType), sizeof(fileHeader.fileType));
	file.read(reinterpret_cast<char*>(&fileHeader.fileSize), sizeof(fileHeader.fileSize));
}

void ReadBmpInfoHeader(ifstream &file, BmpInfoHeader &fileHeader)
{
	int imageWidthOffset = 18;
	int bitsPerPixelOffset = 28;

	file.seekg(imageWidthOffset);

	file.read(reinterpret_cast<char*>(&fileHeader.imageWidth), sizeof(fileHeader.imageWidth));
	file.read(reinterpret_cast<char*>(&fileHeader.imageHeight), sizeof(fileHeader.imageHeight));

	file.seekg(bitsPerPixelOffset);

	file.read(reinterpret_cast<char*>(&fileHeader.bitsPerPixel), sizeof(fileHeader.bitsPerPixel));
	file.read(reinterpret_cast<char*>(&fileHeader.compressionType), sizeof(fileHeader.compressionType));
}

void WriteInfoAboutBmpFile(BmpFileHeader &fileHeader, BmpInfoHeader &infoHeader)
{
	cout << "Size in bytes: " << fileHeader.fileSize << endl;
	cout << "Image width: " << infoHeader.imageWidth << endl;
	cout << "Image height: " << infoHeader.imageHeight << endl;
	cout << "Bits per pixel: " << infoHeader.bitsPerPixel << endl;

	if (infoHeader.bitsPerPixel <= 8)
	{
		switch (infoHeader.bitsPerPixel)
		{
		case 1:
		{
			cout << "This file uses 2 colors (white, black)\n";
			break;
		}
		case 4:
		{
			cout << "This file uses 16 colors\n";
			break;
		}
		case 8:
		{
			cout << "This file uses 256 colors\n";
			break;
		}
		}
	}

	if (infoHeader.compressionType != 0)
	{
		switch (infoHeader.compressionType)
		{
		case 1:
		{
			cout << "This BMP file uses RLE 8-bit / pixel compression method\n";
			break;
		}
		case 2:
		{
			cout << "This BMP file uses RLE 4-bit / pixel compression method\n";
			break;
		}
		case 4:
		{
			cout << "This BMP file uses JPEG compression method\n";
			break;
		}
		case 5:
		{
			cout << "This BMP file uses PNG compression method\n";
			break;
		}
		}
	}
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		cout << "Invalid amount of arguments!\n"
			<< "Usage: bmpinfo.exe <input file name>" << endl;
		return 1;
	}

	ifstream input;

	if (!OpenBinaryFileForReading(input, argv[1]))
	{
		cout << "Can't open " << argv[1] << " for reading!" << endl;
		return 1;
	}

	BmpFileHeader bmpFileHeader;
	BmpInfoHeader bmpInfoHeader;

	ReadBmpFileHeader(input, bmpFileHeader);
	ReadBmpInfoHeader(input, bmpInfoHeader);

	if (bmpFileHeader.fileType != BMP_FILE_TYPE)
	{
		cout << argv[1] << " is not BMP file" << endl;
		return 1;
	}

	WriteInfoAboutBmpFile(bmpFileHeader, bmpInfoHeader);

	return 0;
}