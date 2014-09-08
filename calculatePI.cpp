#include <iostream>
#include <string>
#define POST 5
using namespace std;

class BigInteger{
public:
	BigInteger(string a) {
		m_size = a.size();
		m_pdata = new int[m_size];
		m_beg = 0;
		for (int i = 0; i < a.size(); i++)
		{
			m_pdata[i] = a[i] - '0';
			if (!m_pdata[m_beg])
			    m_beg++;
        }
	}
	~BigInteger() {
		if (m_pdata)
			delete []m_pdata;
	}
	int operator[](int ind) const{
	    return m_pdata[ind];
	}
	int& operator[](int ind) {
	    return m_pdata[ind];
	}
	void print(int n) {
		for (int i = 1; i <= n; i++) {
			cout << m_pdata[i];
			if (i % 10 == 0)
				cout << endl;
		}
		if (n % 10 != 0)
			cout << endl;
	}
	void operator/=(int b) {
		int cur = 0;
		for (int i = m_beg; i < m_size; i++)
		{
			cur = cur * 10 + m_pdata[i];
			m_pdata[i] = cur / b;
			cur %= b;
			if (!m_pdata[m_beg])
			    m_beg++;
		}
	}
	void operator*=(int b) {
		int carry = 0;
		for (int i = m_size - 1; i >= m_beg; i--)
		{
			int tmp = m_pdata[i] * b + carry;
			m_pdata[i] = tmp % 10;
			carry = tmp / 10;
			if (i == m_beg && carry)
			    m_beg--;
		}
	}
	void operator+=(const BigInteger &b) {
		int carry = 0;
		for (int i = m_size - 1; i >= m_beg; i--)
		{
			int tmp = m_pdata[i] + b[i] + carry;
			m_pdata[i] = tmp % 10;
			carry = tmp / 10;
			if (i == m_beg && carry)
			    m_beg--;
		}
	}
	bool operator>(const BigInteger &b) {
        if (m_beg != b.m_beg)
            return m_beg < b.m_beg;
        for (int i = m_beg; i < m_size; i++)
        {
            if (m_pdata[i] != b[i])
                return m_pdata[i] > b[i];
        }
        return false;     
    }
private:
	int *m_pdata;
	int m_size;
	int m_beg;
};

int main() {
	int n;
	while (cin >> n) {
		string two = "2" + string(n + POST, '0');
		string err = string(n + POST, '0') + "1"; 
		
		BigInteger PI(two);
		BigInteger z(two);
		BigInteger error(err);
		int a = 1, b = 3;
        while (z > error)
        {
            z *= a;
            z /= b;
            PI += z;
            a ++;
            b += 2;
        }
		PI.print(n);
	}
}