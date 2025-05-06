#include <stdio.h>                                         
#include <stdlib.h>
#include <math.h>
#pragma warning(disable:4996)


unsigned  k, nrPersImport, nrPersInDrum;
unsigned short id = 0;
double distParcurs, combustibil; 

typedef struct Calls
{
	unsigned short x, y, prioritate, id;
	struct Calls* urm;    

}nevoiasi; 
typedef enum { Very_Low, Low, Medium, High, Very_High } prioritate;
prioritate prio[5]; 
nevoiasi* persImport[100], * persInDrum[100];

void ADD_Call(nevoiasi* prim)
{
	nevoiasi* q, * p;
	id++;
	printf("\nNevoiasul %hu\n", id); 
	p = (nevoiasi*)malloc(sizeof(nevoiasi));
	printf("x= "); scanf("%hu", &p->x);
	printf("y= "); scanf("%hu", &p->y);
	printf("prioritate= "); scanf("%hu", &p->prioritate);
	if ((p->x > 10000) || (p->y > 10000) || (p->prioritate > 4))
	{
		printf("Conditiile initiale nu sunt indeplinite(0<x<10000 , 0<y<10000 , 0<=prioritate<=4\n");
		system("pause");
		exit(0);
	}
	p->urm = NULL;
	p->id = id;
	q = prim; 
	while (q->urm != NULL && q->urm->x < p->x)       
		q = q->urm;
	while (q->urm != NULL && q->urm->x == p->x && q->urm->y < p->y)
		q = q->urm;

	p->urm = q->urm; 
	q->urm = p;

}

double Dist(nevoiasi* p, nevoiasi* q)
{
	return sqrt(pow(q->x - p->x, 2) + pow(q->y - p->y, 2));
}

double SetPriority(nevoiasi* prim, double* distTotala)
{
	nevoiasi* q = prim->urm, * p = prim, * t = prim;
	nrPersImport = 0;
	int i;
	double dist = 0;
	*distTotala = 0;
	for (i = Very_Low; i <= Very_High; i++)                      
		prio[i] = 0;
	persImport[nrPersImport++] = prim;
	while (q)
	{
		*distTotala = *distTotala + Dist(t, q);
		prio[q->prioritate]++;                                                                              
		if (q->prioritate == Very_High && nrPersImport <= k)
		{
			if (dist + Dist(p, q) + Dist(prim, q) <= combustibil)
			{
				dist += Dist(p, q);
				p = q;
				persImport[nrPersImport] = t;
				nrPersImport++;
			}
		}
		t = q;
		q = q->urm;
	}
	*distTotala += Dist(t, prim);
	return dist + Dist(prim, p);
}
void GrowPriority(nevoiasi* prim)
{
	nevoiasi* q = prim->urm;
	while (q)
	{
		if (q->prioritate < Very_High)
			q->prioritate++;
		q = q->urm;
	}
}

void DeleteCall(nevoiasi* p)
{                                         
	nevoiasi* q = p->urm;     
	p->urm = p->urm->urm;   
	free(q);
}

void PersInDrum()
{                     
	nevoiasi* q, * t;
	nrPersInDrum = 0;													
	int i, n = nrPersImport - 1;
	for (i = 0; i < n; i++)
	{											
		q = persImport[i]->urm;
		int a = persImport[i + 1]->urm->x - persImport[i]->urm->x;
		int b = persImport[i + 1]->urm->y - persImport[i]->urm->y;
		if (persImport[i] != persImport[i + 1])
			while (q->urm != NULL && q->urm != persImport[i + 1]->urm)
			{
				t = q;
				q = q->urm;
				if (b * (q->x - persImport[i]->urm->x) == a * (q->y - persImport[i]->urm->y))
				{			
					persInDrum[nrPersInDrum] = t;
					nrPersInDrum++;
				}
			}
	}

}
void Sort()
{  
	int i, ok;
	nevoiasi* aux;
	do {
		ok = 0;
		for (i = nrPersImport - 2; i; i--)
			if (persImport[i]->x > persImport[i + 1]->x || (persImport[i]->x == persImport[i + 1]->x && persImport[i]->y > persImport[i + 1]->y))
			{ 
				aux = persImport[i];
				persImport[i] = persImport[i + 1];
				persImport[i + 1] = aux;
				ok = 1;
			}
	} while (ok);

}
void SortID(unsigned* v, unsigned n) 
{			
	unsigned i, ok, aux;
	do 
	{
		ok = 0;
		for (i = 0; i < n - 1; i++)
			if (v[i] > v[i + 1]) 
			{
				aux = v[i];
				v[i] = v[i + 1];
				v[i + 1] = aux;
				ok = 1;
			}
	} while (ok);
}

int main() 
{
	unsigned days = 1, i, nrCalls = 0, n, * v;
	double distTotala;                          
	nevoiasi* prim = (nevoiasi*)malloc(sizeof(nevoiasi));
	prim->x = 0;
	prim->y = 0;
	prim->prioritate = 0;
	prim->urm = NULL;
	printf("Numarul de pachete ce pot fi livrate intr-o zi: "); scanf("%u", &k);
	do														
	{   
		printf("Ziua %u\n", days);
		printf("Numarul de nevoiasi: "); scanf("%u", &n);      
		for (i = 1; i <= n; i++)
			ADD_Call(prim);
		nrCalls += n;
		combustibil += 10000;
		distParcurs = SetPriority(prim, &distTotala);
		if (distTotala <= combustibil && nrCalls <= k)
		{      
			printf("\nRezumat sfarsit de zi %u:", days);        
			printf("\nAu fost stersi nevoiasii: ");
			combustibil -= distTotala;
			i = 0;
			v = (unsigned*)malloc(sizeof(unsigned) * nrCalls);
			while (prim->urm)
			{
				v[i] = prim->urm->id;
				i++;
				DeleteCall(prim);
			}
			SortID(v, nrCalls);
			for (i = 0; i < nrCalls; i++) 
				printf("%u ", v[i]);
			free(v);
			printf("\nNu se mai afla nici-un apel in lista!");
			printf("\nCombustibil ramas %f L\n", combustibil);  
		}
		else if (prio[Very_High])
		{                                     
			if (k - prio[Very_High])
				PersInDrum();
			combustibil -= distParcurs;                 
			for (i = nrPersInDrum + nrPersImport - k - 1; i < nrPersInDrum; i++)
				persImport[nrPersImport++] = persInDrum[i];
			Sort();
			printf("\nRezumat sfarsit de zi %u:", days);         
			printf("\nAu fost stersi nevoiasii: ");
			v = (unsigned*)malloc(sizeof(unsigned) * nrPersImport);
			for (i = nrPersImport - 1; i; i--) 
			{
				v[i] = persImport[i]->urm->id;
				DeleteCall(persImport[i]);                          
			}
			SortID(v, nrPersImport);
			for (i = 0; i < nrPersImport - 1; i++)
				printf("%u ", v[i]);
			free(v);
			printf("\nCombustibil ramas %f L\n", combustibil);
			printf("Au fost livrate %u pachete\n", nrPersImport - 1);

		}
		else
			printf("Asteptam pana pachetele devin urgente\n");                                           
		system("pause");
		GrowPriority(prim);
		days++;
		nrCalls = nrCalls - nrPersImport + 1;
	} while (prim->urm);
	system("pause");
	return 0;
}