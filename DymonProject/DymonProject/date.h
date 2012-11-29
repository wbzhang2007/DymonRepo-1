//created by Hu Kun on 29 Nov 2012

#ifndef DATE_H
#define DATE_H
namespace utilities {
	class date {
	public:

		date(char* aDate);
		~date();

	private:
		char* dateField;

	};
}
#endif