#pragma once

#include <string>

using uchar = unsigned char;

enum class ImageType {
	Unknow,
	PNG,
	JPG,
	BMP
};

struct ImageSize {
	size_t width;
	size_t height;

	ImageSize(size_t w = 0, size_t h = 0);
};


// TODO: �������� ��� ���������� �������� �������� ��������� rgb � rgba,
// ����� ��� ���� ���������� � ������.
// ������ ��� ������ bmp � jpg ������ ����� �������� ��������������� ������ 
// ������� 3 * ������ * ������ � ������ 4 * ������ * ������.
#pragma pack(push, 1)
struct Pixel {
	uchar red;
	uchar green;
	uchar blue;
	uchar alpha;

	Pixel(uchar r = 0, uchar g = 0, uchar b = 0, uchar alpha = 0);

	size_t metric() const;
	size_t colorAvg() const;
};
#pragma pack(pop)

class AbstractImage;

class PixelMatrix {
public:
	friend AbstractImage;

	PixelMatrix(size_t w = 0, size_t h = 0);
	PixelMatrix(Pixel* data, size_t w = 0, size_t h = 0);

	Pixel* operator[](size_t i) const;

	// ��� ����������� - ������� move-��������� 
	// ������ ����� ����� ���������� � ������, ����� �������� � rvalue (��������� ������)
	// ����: ���� ����� ������������� ������ �� ����� ������ mv, ��� �� ����� ����������
	// ������, � ����� ������ ���������� ��������� �� ������ ������� � ������, ��� ����
	// ������-�������� ������� ����������� �������� � ��������� ��������� ���������
	PixelMatrix& operator=(PixelMatrix&& mv) noexcept;

	void moveFrom(PixelMatrix& mv);

	~PixelMatrix();
private:
	Pixel* _data;
	size_t _height;
	size_t _width;
};

class AbstractImage
{
public:
	virtual ~AbstractImage();

	ImageType	type() const;
	size_t		height() const;
	size_t		width() const;
	ImageSize	size() const;

	static AbstractImage* create(const std::string& fileName, ImageType type = ImageType::Unknow);	// ��������� �����

	void resize(const ImageSize& size);				// �������� ������
	void resize(const size_t w, const size_t h);	// ���������� ��������� �������
	void widthResize(const size_t width);			// �������� ������
	void heightResize(const size_t height);			// �������� ������
	void toBlackWhite();							// ���������� � ��
	void toNegative();								// ���������� � �������
	void toColorInversion();						// �������� ������
	
	// use your imagination: ���� ������� ��������, �� ������ ����������� ����� �������

	virtual void save(const std::string& output) = 0;
	virtual std::string stringType() const = 0;		// ".png" � �.�.
protected:
	AbstractImage();
	PixelMatrix		_pixelData;
	ImageType		_type;
	size_t			_dataSize;
	size_t			_channelCount;

	Pixel* pixelLine(size_t i);
	Pixel& pixelAt(size_t i, size_t j);

	uchar* rawData();
};

