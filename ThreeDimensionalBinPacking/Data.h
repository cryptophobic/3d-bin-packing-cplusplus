#pragma once
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include "Logger.h"

namespace DataTypes 
{
	class Size 
	{
	public:
		Size(Size* size);
		Size();
		~Size();

		long GetVolume();
		int GetWidth();
		int SetWidth(int width);

		int GetHeight();
		int SetHeight(int height);

		int GetDepth();
		int SetDepth(int depth);

		std::string ToString();

	private:
		int width;
		int depth;
		int height;
		long volume;

	};

	class Axis 
	{
	public:

		int X;
		int Y;
		int Z;

		Axis();
		Axis(int xyz);
		Axis(int x, int y, int z);
		~Axis();
		std::string ToString();
	};

	class BigAndHeavy : public Size 
	{

	public:
		BigAndHeavy();
		long Weight;
		std::string ToString();
	};

	class Product : public BigAndHeavy	
	{
	public:
		std::string ProdId;
		std::string Name;
		std::string ToString();
	};

	class Container : public BigAndHeavy 
	{

	public:
		Container();
		~Container();
		bool isFit(Product* box);
		std::string ToString();

	protected:
		Stat::Logger *logger;
		bool possibleToPut(Size* boxSize, Axis* dot);

	};

	class Pack : public Product, public Axis
	{

	public:
		Pack();
		~Pack();
		std::string ToString();
	};

	class FilledContainer : private Container 
	{
	public:
		FilledContainer();
		~FilledContainer();
		long GetPackedCount();
		long GetPackedVolume();
		long GetFreeVolume();

		std::map<long, Pack*>* getProductsCol();
		void setProductsCol(std::map<long, Pack*>* value);

		std::vector<Pack*>* getProducts();
		void setProducts(std::vector<Pack*>* value);

	private:
		long packedVolume;
		long freeVolume;
		std::vector<Pack*>* products_arr;
		std::map<long, Pack*>* products_col;
		void clearProducts();
		void clearProductCol();


	};

}