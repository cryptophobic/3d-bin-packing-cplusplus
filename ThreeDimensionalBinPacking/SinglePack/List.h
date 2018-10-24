#include "../Data.h"
#include "../Logger.h"

using namespace DataTypes;
using namespace Stat;

namespace SinglePack
{

	extern struct ListHigh;
	extern struct ListMiddle;
	extern struct ListBottom;

	class List 
	{
	private:
		struct ListHigh
		{
		public:
			ListHigh* prev;
			ListHigh* next;
			ListMiddle* down;
			int value;
			int count;
		};

		struct ListMiddle
		{
		public:
			ListMiddle* prev;
			ListMiddle* next;
			ListBottom* down;
			ListHigh* up;
			int value;
			int count;

		};

		struct ListBottom 
		{
		public:
			ListBottom* prev;
			ListBottom* next;
			ListMiddle* up;
			int value;
			int box;
		};

		ListHigh* listY;
		ListMiddle* listX;
		ListBottom* listZ;
		ListHigh* first;
		ListBottom* current;

		Logger logger;

		
	};
}