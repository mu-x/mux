#include "Sensor.h"

int			i,j,jj1,jj2;
float		t,jtim,r,r1,r2,r3,r4,delt,tau,dx;
long int	h,m,s,s100;
struct tm*	mytime;
massiv		wspom;

// Имитатор об"екта исследования
// KANAL - номер канала опроса
// XIZM - результат измерения по каналу
// WSPOM - вспомогательный массив типа REAL  с 52 элементами.

float initdat(void)
{
	int i;
	float rr,rr4,rt;

	time_t nowtime;
	time(&nowtime);
	mytime = localtime(&nowtime);

	rr=mytime->tm_sec;
	rr4=mytime->tm_min;
	rr=rr+60*rr4;
	rr4=mytime->tm_hour;
	rr=rr+3600*rr4;
	do {
		rr-=1000;
	} while(rr>32767);
	i=(int)rr;
	rr4=i;
	rt=(rr-rr4)*1.0E+5+7127.1;
	return rt;
};


// Датчик равномерно распределенных [0,1]
// псевдослучайных чисел

void randd(float * dxx,float * rr) 
{
	float dy = 117239.7;
	float rrr,rrr1;
	rrr=4; (*dxx)*=5;
	do {
		rrr1=rrr*dy;
		if ((*dxx)>rrr1) (*dxx)-=rrr1;
		rrr=rrr*0.5;
	} while(rrr>0.9);
	(*rr)=(*dxx)/dy;
};


// Генерация псевдослучайных нормальных чисел

float gauss( float r,float s)
{
	int i;
	float r2,r1;
	r1=0;
	for(i=1;i<12;i++) {
		randd(&dx,&r2); r1=r1+r2;
	};
	r1=(r1-6)*s+r;
	return r1;
}; /* GAUSS */


// Генерация независимых переменных
void izmer7(int j)
{
	float r,rr;
	time_t nowtime;
	time(&nowtime);
	mytime = localtime(&nowtime);

	rr=mytime->tm_sec;
	r= mytime->tm_min;
	rr+=60*r;
	r=mytime->tm_hour;
	rr+=3600*r;
	wspom[11]=rr;
	randd(&dx,&r);
	if (j==1) wspom[1]=-20+50*r;
	else
		if (j==2) wspom[2]=740+30*r;
		else
			if (j==3) wspom[3]=50+50*r;
			else
				if (j==4) {
					wspom[4]=0;
					if (r>0.5) wspom[4]=1;
				}
				else
					if (j==5) {
						wspom[5]=2;
						if (r<=0.33333) wspom[5]=1;
						else
							if (r>=0.666667) wspom[5]=3;
					}
					else
						if (j==6) {
							wspom[6]=0;
							if (r>0.5) wspom[6]=1;
						};
}; /* IZMER7 */


float opros(int kanal)
{
	// Начало основной части процедуры OPROS
	float xizm;
	dx=wspom[12];
	if ((dx<0.1)||(dx>1.0E+6)) dx=initdat();
	if (kanal>=1) {
		time_t nowtime;
		time(&nowtime);
		mytime = localtime(&nowtime);

		r4=mytime->tm_sec;
		delt=mytime->tm_min;
		r4+=60*delt;
		delt=mytime->tm_hour;
		r4+=3600*delt;
		delt=r4-wspom[11]-180;
		if (kanal<=10) {
			/* Независимые переменные */
			wspom[11]=0;
			if (kanal <= 6) izmer7(kanal);
			r=wspom[kanal];
		}
		else
			if (kanal<=70) {
				r4=0; r=1; r1=gauss(r4,r);
				if (kanal<=25) {
					/* Лин. регресс. модель - пассивный эксперимент */
					jj1=kanal-11;
					jj2=kanal-18;
					r=30+jj1*5-(5-jj2*0.14)*wspom[1]+(0.6-jj1*0.014)*wspom[2]+
						(350-jj1*10)*wspom[4]-(3-jj2*0.07)*wspom[1]*wspom[4]+
						(0.05+jj1*0.001)*wspom[1]*wspom[3]+0.01*wspom[3]*wspom[3];
					r1=5*r1;
				}
				else
					if (kanal <= 40) {
						/* Лин. регресс. модель - активно-пассивный эксперимент */
						jj1=kanal-26; jj2=kanal-33;
						r=100+jj1*20+(7+jj1*0.5)*wspom[1]+(0.6+jj2*0.01)*wspom[2]-
							(15+jj1*2)*wspom[5]+(4+jj2*0.1)*wspom[7]+
							(40+jj1*2)*wspom[8]+(0.01+jj2*0.0005)*wspom[1]*wspom[2]-
							(0.5+jj2*0.01)*wspom[7]*wspom[8]+(0.7-jj1*0.02)*wspom[5]*
							wspom[7]-(0.15-jj1*0.01)*wspom[1]*wspom[1]+(30-jj1*1.4)*
							wspom[8]*wspom[8] ;
						r1=5*r1;
					}
					else
						if (kanal <= 55) {
							/* Нелин. модель - пассивный эксперимент */
							r=30+(kanal-41)*3+(10+(kanal-48)*0.5)*exp((0.055-
								(kanal-41)*0.001)*wspom[1])-(2+(kanal-50)*0.1)*
								exp(0.07*wspom[1]-(0.0001+(kanal-46)*0.00002)*wspom[2]+
								(1+(kanal-48)*0.06)*wspom[4]);
							r1=1.5*r1;
						}
						else
							if (kanal <= 70) {
								/* Нелинейная модель - активно-пассивный эксперимент */
								jj1=kanal-56; jj2=kanal-63;
								r=60+(kanal-65)*3+(-5.5+jj1*0.1)*exp((0.05+jj1*0.001)*
									wspom[1]+(-0.1+jj2*0.006)*wspom[9])+(9-jj1*0.2)*
									exp((-0.55+jj1*0.01)*wspom[10]+(0.7+jj2*0.03)*wspom[5]);
								r1=1.5*r1;
							};
				r=r+r1;
			}
			else
				if (kanal <= 85) {
					/* Динамическая модель - инерционное звено */
					time_t nowtime;
					time(&nowtime);
					mytime = localtime(&nowtime);

					jtim=mytime->tm_sec;
					r4=  mytime->tm_min;
					jtim+=60*r4;
					r4=  mytime->tm_hour;
					jtim+=3600*r4;
					tau=15-(kanal-71)*0.4;
					r=0; r3=0;
					for (i=20;i>=1;i--) {
						r2=jtim-wspom[i+12]; r2=r2/tau;
						if (r2<=50) r=r+(wspom[i+32]-r3)*(1-exp(-r2));
						r3=wspom[i+32];
					};
					r=(20+(kanal-78)*2)*r;
					/* for i:=1 to 20 do writeln(wspom[i+12]:10:3,wspom[i+32]:10:3) */
				}
				else {
					jj1=kanal-100; r1=jj1*0.1; r4=1;
					r=gauss(r1,r4);
				};
	};
	xizm=r;
	wspom[12]=dx;
	return xizm;
};

void uprav(int kanal,float upr ,massiv wspom)
{
	/* Имитация подачи управл. воздействия на об'ект */
	typedef float mm[4];
	int  i,i1,j1;
	float jtim,r;
	mm umin,umax;

	umin[0]=-70; umax[0]=-umin[0];
	umin[1]=-3;  umax[1]=-umin[1];
	umin[2]=-5;  umax[2]=-umin[2];
	umin[3]=-2.5;umax[3]=-umin[3];
	if ((kanal < 7) || (kanal > 10))
		printf("ОШИБКА UPRAV : канал N\n");  /*,kanal:7,' упр.возд.=',upr:10:3)*/
	else {
		j1=kanal-6;
		if (upr>umax[j1]) upr=umax[j1];
		else
			if (upr<umin[j1]) upr=umin[j1];
		wspom[kanal]=upr;
		if (kanal==10)
			if (abs(wspom[33]-upr)>=0.01) {
				time_t nowtime;
				time(&nowtime);
				mytime = localtime(&nowtime);

				jtim=mytime->tm_sec;
				jtim=mytime->tm_sec;
				r=mytime->tm_min;
				jtim+=60*r;
				r=h;
				jtim+=3600*r;
				for(i=2;i<20;i++) {
					i1=22-i; wspom[i1+32]=wspom[i1+31];
					wspom[i1+12]=wspom[i1+11];
				};
				wspom[33]=upr; wspom[13]=jtim;
			};
	};
};
