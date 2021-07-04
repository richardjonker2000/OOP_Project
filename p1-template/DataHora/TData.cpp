///////////////TData.cpp (vrs. 12/Nov/2014)////////////////
#include "TData.h"
#include<iostream>
#include<sstream> // string stream


TData::TData(){}

TData::TData(int d, int m, int a){ set(d,m,a);}

void TData::set(const string &dat){
	if (dat.compare("HOJE")==0) *this=hoje();
	else{
		int d, m, a;
		string vdat(dat), str;
		for(unsigned int i=0; i<vdat.size(); i++) if(vdat[i]=='-') vdat[i]='/';
		istringstream xx(vdat);
		getline(xx, str, '/');
		try{
			d=stoi(str,NULL);
		}catch (const std::invalid_argument& ia){
			std::cerr << "Formato invalido: " << ia.what() << '\n';
			d=1;
		}
		str.erase();
		getline(xx, str, '/');
		try{
			m=stoi(str,NULL);
		}catch (const std::invalid_argument& ia){
			std::cerr << "Formato invalido: " << ia.what() << '\n';
			m=1;
		}
		str.erase();
		getline(xx, str, '/');
		try{
			a=stoi(str,NULL);
		}catch (const std::invalid_argument& ia){
			std::cerr << "Formato invalido: " << ia.what() << '\n';
			a=1;
		}
		set(d,m,a);
	}
}

TData::TData(const string &dat){ set(dat);}

TData::TData(const char *dat){ set(dat);}

bool TData::setDia(int d){if(dataValida(d,mes,ano)) {dia=d; return true;} else return false;}
bool TData::setMes(int m){if(dataValida(dia,m,ano)) {mes=m; return true;} else return false;}
bool TData::setAno(int a){if(dataValida(dia,mes,a)) {ano=a; return true;} else return false;}

bool TData::set(int d, int m, int a){
	if(a<50) a+=2000;
	else if(a<100) a+=1900;
	if(dataValida(d,m,a)) {dia=d; mes=m; ano=a; return true;}
	else {cout<<d<<'/'<<m<<'/'<<a<<": Data invalida!\n"; dia=mes=ano=1; return false;}
}

void TData::operator=(const string &dat){ set(dat);}

int TData::getDia() const{return dia;}
int TData::getMes() const{return mes;}
int TData::getAno() const{return ano;}

int TData::idade() const{
	TData hoje("HOJE");
	if(hoje.getMes()>getMes() || (hoje.getMes()==getMes() && hoje.getDia()>=getDia()))
		 return hoje.getAno()-getAno();
    else return hoje.getAno()-getAno()-1;
}

string TData::data_str() const{
	static const string int2mes[13]={"", "Jan","Fev","Mar","Abr","Mai","Jun",
									     "Jul","Ago","Set","Out","Nov","Dez"};
	ostringstream xx;
	xx<<(dia<10?"0":"")<<dia<<'/'<<int2mes[mes]<<'/';
	if(ano>=2050) xx<<ano;
	else if(ano>=2010) xx<<ano-2000;
		 else if(ano>=2000) xx<<0<<ano-2000;
		      else if(ano>=1950) xx<<ano-1900;
			       else xx<<ano;
	return xx.str();
}

string TData::DiaDaSemana() const{
	string ss(diaDaSemana());
	ss.front()=ss.front()+'A'-'a';
	return ss;
}

string TData::diaDaSemana() const{
	static const string int2dia[8] = { "", "domingo", "segunda-feira", "ter\207a-feira",
		"quarta-feira", "quinta-feira", "sexta-feira", "s\240bado" };
	long ndias = *this - TData("1/1/100");
	return int2dia[(ndias + 5) % 7 + 1];
}

string TData::mesDoAno() const{
	static const string int2mes[13] = { "", "janeiro", "fevereiro", "mar\207o",
		"abril", "maio", "junho", "julho", "agosto", "setembro", "outubro", "novembro", "dezembro"};
	return int2mes[mes];
}

string TData::MesDoAno() const{
	string ss(mesDoAno());
	ss.front() = ss.front() + 'A' - 'a';
	return ss;
}

bool TData::dataValida(int d, int m, int a){ return d >= 1 && d <= ultimoDiadoMes(m, a) && m >= 1 && m <= 12 && a >= 100; }

bool TData::bissexto(int a){return a%400==0 || (a%4==0 && a%100!=0);}

int TData::ultimoDiadoMes(int m, int a){
    switch(m){
      case  2: if (bissexto(a)) return 29;
               else return 28;
      case  4: case 6: case 9: case 11: return 30;
      default: return 31;
    }
}

bool TData::operator<(const TData &outra) const{
	if(ano!=outra.ano) return ano<outra.ano;
	else if(mes!=outra.mes) return mes<outra.mes;
		 else return dia<outra.dia;
}

bool TData::bissexto() const{ return bissexto(ano);}
int TData::ultimoDiadoMes() const{ return ultimoDiadoMes(mes,ano);}
int TData::diaDoAno() const{
    int ndias=0, m;
    for(m=1; m<mes; m++) ndias+=ultimoDiadoMes(m, ano);
    ndias+=dia;
    return ndias;
}
long TData::operator-(const TData &outra) const{
	long ndias=0; int a;
    for(a=outra.ano; a<ano; a++)
      if (bissexto(a)) ndias+=366;
      else ndias+=365;
	ndias-=outra.diaDoAno();
    ndias+=diaDoAno();
    return ndias;
}

long TData::diasJaPassados() const{ return hoje()-*this;}

bool TData::operator>(const TData &outra) const{return outra<(*this);}
bool TData::operator!=(const TData &outra) const{return (*this)<outra||outra<(*this);}
bool TData::operator==(const TData &outra) const{return !((*this)!=outra);}
bool TData::operator<=(const TData &outra) const{return !((*this)>outra);}
bool TData::operator>=(const TData &outra) const{return !((*this)<outra);}

TData TData::hoje(){
	time_t clock;   time(&clock);
	tm reg; localtime_s(&reg, &clock);
	TData dat(reg.tm_mday,reg.tm_mon+1,reg.tm_year+1900);
	return dat;
}

ostream &operator<<(ostream &os, const TData &dat){
	os<<dat.data_str();
	return os;
}

istream &operator>>(istream &is, TData &dat){
	string str;
	is>>str;
	dat.set(str);
	return is;
}

//Paulo Gouveia