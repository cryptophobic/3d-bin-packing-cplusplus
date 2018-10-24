#include "Data.h"
#include <exception>


using namespace DataTypes;

Size::Size() 
{
	this->volume = -1;
	this->height = -1;
	this->width = -1;
	this->depth = -1;
}

Size::Size(Size* size) 
{
	this->SetHeight(size->GetHeight());
	this->SetWidth(size->GetWidth());
	this->SetDepth(size->GetDepth());
}

Size::~Size () {
}

long Size::GetVolume() 
{
	if (this->volume == -1) 
		this->volume = this->depth * this->width * this->height;

	return this->volume;
}

int Size::GetWidth() 
{
	return this->width;
}

int Size::SetWidth(int width) 
{
	if (width < 0) 
	{
		throw new std::exception("Size::SetWidth: cannot set the width to negative");
	}
	if (width != this->width) 
	{
		this->width = width;
		this->volume = -1;
	}

	return this->width;
}

int Size::GetHeight() 
{
	return this->height;
}

int Size::SetHeight(int height) 
{
	if (height < 0) 
	{
		throw new std::exception("Size::SetHeight: cannot set the height to negative");
	}

	if (height != this->height) 
	{
		this->height = height;
		this->volume = -1;
	}

	return this->height;
}

int Size::GetDepth() 
{
	return this->depth;
}

int Size::SetDepth(int depth) 
{
	if (depth < 0) 
	{
		throw new std::exception("Size::SetDepth: cannot set the depth to negative");
	}

	if (depth != this->depth) 
	{
		this->depth = depth;
		this->volume = -1;
	}

	return this->depth;
}

std::string Size::ToString() 
{
	std::stringstream out;
	out << "width = " << this->width << ", height = " << this->height << ", depth = " << this->depth;
	return out.str();
}

BigAndHeavy::BigAndHeavy() : Size()
{
	this->SetDepth(0);
	this->SetWidth(0);
	this->SetHeight(0);
	this->Weight = 0;
}

std::string BigAndHeavy::ToString()
{
	std::stringstream out;
	out << ", weight = " << this->Weight;
	return Size::ToString().append(out.str());
}

Axis::Axis() 
{
	this->X = this->Y = this->Z = -1;
}

Axis::Axis(int xyz) 
{
	this->X = this->Y = this->Z = xyz;
}

Axis::Axis(int x, int y, int z) 
{
	this->X = x;
	this->Y = y;
	this->Z = y;
}

Axis::~Axis() {
}

std::string Axis::ToString() 
{
	std::stringstream out;
	out << "x = " << this->X << ", y = " << this->Y << ", z = " << this->Z;
	return out.str();
}

std::string Product::ToString() 
{
	std::stringstream out;
	out << ", name = " << this->Name << ", ProdId = " << this->ProdId;
	return BigAndHeavy::ToString().append(out.str());
}

Container::Container() 
{
	logger = new Stat::Logger("d:\\newlog.txt");
}

Container::~Container()
{
}

bool Container::isFit(Product* box) 
{
	try 
	{
		if (box->Weight > this->Weight) return false;
		Size *boxSize = new Size();

		Axis *axis = new Axis(0,0,0);
		for (int i = 0; i <= 5; i++)
		{
			if (i > 0)
			{
				if (i % 2 == 0)
				{
					int swap = boxSize->GetWidth();
					boxSize->SetWidth(boxSize->GetHeight());
					boxSize->SetHeight(swap);
				}
				else
				{
					int swap = boxSize->GetDepth();
					boxSize->SetDepth(boxSize->GetWidth());
					boxSize->SetWidth(swap);
				}
			}

			if (this->possibleToPut(boxSize, axis) == false) continue;

			delete axis;
			return true;
		}
	}
	catch(std::exception& e) 
	{
		std::stringstream out;
		out << "Container::isFit: " << e.what();
		logger->Append(out.str(), Stat::Logger::ERROR);
	}
	return false;
}

bool Container::possibleToPut(Size *boxSize, Axis *dot){
	try {
		if (dot->X + boxSize->GetWidth() > this->GetWidth())
			return false;
		if (dot->Y + boxSize->GetHeight() > this->GetHeight())
			return false;
		if (dot->Z + boxSize->GetDepth() > this->GetDepth())
			return false;
		return true;
	}
	catch(std::exception& e) 
	{
		std::stringstream out;
		out << "Container::possibleToPut: " << e.what();
		logger->Append(out.str(), Stat::Logger::ERROR);
	}
	return false;
}

std::string Container::ToString() 
{
	std::stringstream out;
	out << ", weight = " << this->Weight << " ";
	return BigAndHeavy::ToString().append(out.str());
}

Pack::Pack() {}
Pack::~Pack() {}

std::string Pack::ToString() 
{
	return Axis::ToString();
}

FilledContainer::FilledContainer() 
{
	this->products_col = NULL;
	this->products_arr = NULL;
	this->packedVolume = -1;
	this->freeVolume = -1;
}

FilledContainer::~FilledContainer() 
{
	this->clearProductCol();
	this->clearProducts();
}

long FilledContainer::GetPackedCount()
{
	if (this->products_arr->size() == 0)
		return -1;

	return this->products_arr->size();
}

long FilledContainer::GetPackedVolume()
{
	if (this->packedVolume == 0)
	{
		for (std::vector<Pack*>::iterator it = this->products_arr->begin(); it < this->products_arr->end(); it++) 
		{
			this->packedVolume += (*it)->GetVolume();
		}
	}
	return this->packedVolume;
}

long FilledContainer::GetFreeVolume()
{
	if (this->freeVolume == -1 && this->GetVolume() != -1 && this->GetPackedVolume() > 0) 
	{
		this->freeVolume = this->GetVolume() - this->GetPackedVolume();
	}

	return this->freeVolume;
}

void FilledContainer::clearProductCol()
{
	if (this->products_col != NULL) {
		for (std::map<long, Pack*>::iterator it = this->products_col->begin(); it != this->products_col->end(); it++)	
		{
			delete (*it).second;
		}
		this->products_col->clear();
		this->products_col = NULL;
	}
}

void FilledContainer::setProductsCol(std::map<long, Pack*>* value) 
{
	try {
		if (value == NULL) 
		{
			this->clearProductCol();
		} else {
			this->products_col = value;
		}
	}
	catch(std::exception& e) 
	{
		std::stringstream out;
		out << "FilledContainer::setProductsCol: " << e.what();
		logger->Append(out.str(), Stat::Logger::ERROR);
	}

}

std::map<long, Pack*>* FilledContainer::getProductsCol() 
{
	return this->products_col;
}

void FilledContainer::clearProducts()
{
	if (this->products_arr != NULL) {
		for (std::vector<Pack*>::iterator it = this->products_arr->begin(); it < this->products_arr->end(); it++)	
		{
			delete (*it);
		}
		this->products_arr->clear();
		this->products_arr = NULL;
	}
}

void FilledContainer::setProducts(std::vector<Pack*>* value)
{
	try 
	{
		if (value == NULL) 
		{
			this->clearProducts();
		} 
		else 
		{
			this->products_arr = value;
		}
	}
	catch(std::exception& e) 
	{
		std::stringstream out;
		out << "FilledContainer::setProducts: " << e.what();
		logger->Append(out.str(), Stat::Logger::ERROR);
	}
}

std::vector<Pack*>* FilledContainer::getProducts()
{
	return this->products_arr;
}