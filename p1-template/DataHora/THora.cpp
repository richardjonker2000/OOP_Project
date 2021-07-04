///////////////THora.cpp (vrs. 15/Out/2013)////////////////
#include "THora.h"
#include<iostream>
#include<sstream> // string stream


THora::THora(){}

THora::THora(int h, int m, double s){set(h,m,s);}

void THora::set(const string &temp){
	if (temp.compare("AGORA")==0) *this=agora();
	else{
		int h, m; double s;
		string str;
		istringstream xx(temp);
		getline(xx, str, ':');
		try{
			h=stoi(str,NULL);
		}catch (const std::invalid_argument& ia){
			if(!str.empty()) std::cerr << "Formato invalido: " << ia.what() << '\n';
			h=0;
		}
		str.erase();
		getline(xx, str, ':');
		try{
			m=stoi(str,NULL);
		}catch (const std::invalid_argument& ia){
			if(!str.empty()) std::cerr << "Formato invalido: " << ia.what() << '\n';
			m=0;
		}
		str.erase();
		getline(xx, str);
		try{
			s=stod(str,NULL);
		}catch (const std::invalid_argument& ia){
			if(!str.empty()) std::cerr << "Formato invalido: " << ia.what() << '\n';
			s=0;
		}
		set(h,m,s);
	}
}

THora::THora(const string &temp){set(temp);}

THora::THora(const char *temp){set(temp);}

bool THora::setHora(int h){if(tempoValido(h,minuto,segundo)) {hora=h; return true;} else return false;}
bool THora::setMinuto(int m){if(tempoValido(hora,m,segundo)) {minuto=m; return true;} else return false;}
bool THora::setSegundo(double s){if(tempoValido(hora,minuto,s)) {segundo=s; return true;} else return false;}

bool THora::set(int h, int m, double s){
	if(!tempoValido(h,m,s)) {hora=minuto=0; segundo=0.0; return false;}
	else{
		hora=h; minuto=m; segundo=s;
		if(s>=60.0){
			minuto+=int(s)/60;
			segundo-=(int(s)/60)*60;
		}
		if(minuto>=60){
			hora+=minuto/60;
			minuto=minuto%60;
		}
		return true;
	}
}

void THora::operator=(const string &temp){ set(temp);}

int THora::getHora() const{return hora;}
int THora::getMinuto() const{return minuto;}
double THora::getSegundo() const{return segundo;}

double THora::totalHoras() const{return hora+(minuto+segundo/60.0)/60.0;}
double THora::totalMinutos() const{return hora*60+minuto+segundo/60.0;}
double THora::totalSegundos() const{return (hora*60+minuto)*60+segundo;}

string THora::tempo_str() const{
	ostringstream xx;
	xx<<(hora<10?"0":"")<<hora<<':'<<(minuto<10?"0":"")<<minuto<<':'<<(segundo<10.0?"0":"")<<int(segundo);
	return xx.str();
}

bool THora::tempoValido(int h, int m, double s){return !(h<0||m<0||s<0.0);}

bool THora::operator<(const THora &outra) const{
	if(hora!=outra.hora) return hora<outra.hora;
	else if(minuto!=outra.minuto) return minuto<outra.minuto;
		 else return segundo<outra.segundo;
}

THora THora::operator-(const THora &outra) const{
	THora t;
	double ds=totalSegundos()-outra.totalSegundos();
	if (ds<0.0) t.set(0,0,0.0);
	else t.set(0,0,ds);
	return t;
}

THora THora::operator+(const THora &outra) const{
	return THora(hora+outra.hora, minuto+outra.minuto, segundo+outra.segundo);
}

bool THora::operator>(const THora &outra) const{return outra<(*this);}
bool THora::operator!=(const THora &outra) const{return (*this)<outra||outra<(*this);}
bool THora::operator==(const THora &outra) const{return !((*this)!=outra);}
bool THora::operator<=(const THora &outra) const{return !((*this)>outra);}
bool THora::operator>=(const THora &outra) const{return !((*this)<outra);}

THora THora::agora(){
	time_t clock;   time(&clock);
	tm reg; localtime_s(&reg, &clock);
	THora temp(reg.tm_hour, reg.tm_min, reg.tm_sec);
	return temp;
}

ostream &operator<<(ostream &os, const THora &temp){
	os<<temp.tempo_str();
	return os;
}

istream &operator>>(istream &is, THora &temp){
	string str;
	is>>str;
	temp.set(str);
	return is;
}

//Paulo Gouveia