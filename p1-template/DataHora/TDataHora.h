///////////////TDataHora.h////////////////
// representa data e tempo
// apenas permite datas a partir do ano 100
// atualização: 3/Out/2013
// atualização: 15/Out/2013 (construtor por defeito deixou de criar o objecto com a data e hora atual;
//							 sempre que um método receba como parâmetro a string "HOJE_AGORA", em vez
//							 de uma data e hora, essa string é interpretada como representando a data e hora atual)
// atualização: 17/Out/2013 (passou a ser possível subtrair datahoras)
// atualização: 12/Nov/2014 (o método getStr() passou a datahora_str() )

#pragma once
#include"TData.h"
#include"THora.h"

class TDataHora: public TData, public THora{
public:
	TDataHora();							
	TDataHora(int d, int m, int a, int h, int min, double s);		// cria o objeto com d/m/a h:min:s
	TDataHora(const TData &d, const THora &t);	// cria o objeto com a data d e o tempo t
	TDataHora(const string & dt);			// cria o objeto com a datatempo expressa na string dt (string com uma datatempo no formato "x/x/xxxx h:m:s" ou "x-x-xx h:m:s")
	TDataHora(const char *dt);				// cria o objeto com a data expressa na string tipo C dt (string com uma datatempo no formato "x/x/xxxx h:m:s" ou "x-x-xx h:m:s")
	bool set(int d, int m, int a, int h, int min, double s); // d/m/a h:min:s
	void set(const string &dt);				// dt: string com uma datatempo no formato "x/x/xxxx h:m:s" ou "x-x-xx h:m:s"
	void setData(const TData &d);				
	void setTempo(const THora &t);				
	void operator=(const string &dt);		// dt: string com uma datatempo no formato "x/x/xxxx h:m:s" ou "x-x-xx h:m:s"
	string datahora_str() const;					// devolve uma string com a data e tempo ("x/x/xx h:m:s")
	TData getData() const;
	THora getTempo() const;
	THora operator-(const TDataHora &outra) const; //devolve o tempo decorrido entre a datahora 'outra' e a datahora representada no objeto atual
												   //devolve o tempo 0:0:0 se a datahora 'outra' for maior que a datahora representada no objeto atual
	bool operator<(const TDataHora &outra) const;
	bool operator>(const TDataHora &outra) const;
	bool operator==(const TDataHora &outra) const;
	bool operator!=(const TDataHora &outra) const;
	bool operator<=(const TDataHora &outra) const;
	bool operator>=(const TDataHora &outra) const;
	static TDataHora hoje_agora();
};

ostream &operator<<(ostream &os, const TDataHora &dt);
istream &operator>>(istream &is, TDataHora &dt);