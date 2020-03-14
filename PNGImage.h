#pragma once

#include <string>
#include"AbstractImage.h"

class PNGImage final : public AbstractImage // final ��� ��������, ��� ����� ������ �� ����� �������������
{
public:
	PNGImage(const std::string& fileName);

	void save(const std::string& outputName) override;
	std::string stringType() const override;
};

