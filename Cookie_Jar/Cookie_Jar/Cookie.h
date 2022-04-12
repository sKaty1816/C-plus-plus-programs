#pragma once

class Cookie {
public:
	Cookie();
	Cookie(const Cookie& other);
	const Cookie& operator=(const Cookie& other);
	~Cookie();
	bool isEmpty() const;
	void addFeature(const char* feature);
	void deleteArray(char** arr, int sizeArr);
	void copyCookie(const char** other, int sizeArr);
	const char** getCookie() const;
	const int getSize() const;
	void printCookie() const;
private:
	char** cookie;
	int sizeArr;
};