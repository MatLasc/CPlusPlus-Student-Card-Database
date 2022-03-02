#include <iostream>
#include<cstring>
#include<algorithm>


using namespace std;

#define MAX_MATERII 10


class Student{
   private:
    char *nume, *prenume;
    int nr_materii;
    float medie_generala;

    //setterii clasei Student
    void set_nume(char *nume){
        this -> nume = new char[strlen(nume) + 1];
        strcpy(this -> nume, nume);
    }
    void set_prenume(char *prenume){
        this -> prenume = new char[strlen(prenume) + 1];
        strcpy(this -> prenume, prenume);
    }

    void set_nr_materii(int nr_materii){
        this -> nr_materii = nr_materii;
    }
    void set_medie_generala(int medie_generala){
        this->medie_generala = medie_generala;
    }

   public:
    class Carnet_de_note{
        int medie;
        int nr_credite;
        // setterii clasei Carnet_de_note
        void set_medie(int medie){
            this -> medie = medie;
        }
        void set_nr_credite(int nr_credite) {
            this->nr_credite = nr_credite;
        }
        public:
        // constructorii clasei Carnet_de_note
        Carnet_de_note(){ // implicit
            medie = 0;
            nr_credite = 0;
        }

        Carnet_de_note(Carnet_de_note &materie){ // de copiere
            this -> medie = materie.medie;
            this -> nr_credite = materie.nr_credite;
        }

        Carnet_de_note(int medie, int nr_credite){ //cu parametrii
            this -> medie = medie;
            this -> nr_credite = nr_credite;
        }
        Carnet_de_note& operator=(const Carnet_de_note &materie);
        friend istream &operator>>(istream &is, Carnet_de_note &materie); // supraincarcarea citirii clasei Carnet_de_note


        //getteri pentru Carnet_de_note
        int intoarce_medie(){
          return this->medie;
        }
        int intoarce_nr_credite(){
            return this -> nr_credite;
        }


    } ;
    private:
        Carnet_de_note materii[MAX_MATERII];
    public:
    // constructorii clasei Student
    Student(){ // implicit
        this -> nume = nullptr;
        this -> prenume = nullptr;
        nr_materii = 0;
        medie_generala = 0;
    }

    Student(Student &student){//de copiere
        this -> nume = new char[strlen(student.nume + 1)];
        this -> prenume = new char[strlen(student.prenume + 1)];
        strcpy(this -> nume,student.nume);
        strcpy(this -> prenume, student.prenume);
        this -> nr_materii = student.nr_materii;
        this -> medie_generala = student.medie_generala;
    }

    Student(char *nume , char *prenume, int nr_materii,float medie_generala){ // cu parametrii
        this -> nume = new char[strlen(nume) + 1];
        strcpy(this -> nume, nume);
        this -> prenume = new char[strlen(nume) + 1];
        strcpy(this -> prenume, prenume);
        this -> nr_materii = nr_materii;
        this -> medie_generala = medie_generala;
    }

    public:
    //getteri pentru Student
    char *intoarce_nume() {
        return nume;
    }
    char *intoarce_prenume(){
        return prenume;
    }
    int intoarce_nr_materii(){
        return nr_materii;
    }
    friend istream &operator>>(istream &is, Student &student); // supraincarcarea citirii pentru clasa Student
    Student operator=(const Student& student);


    float calcul_medie_generala();// calculul mediei generale
    static Student* sort_dupa_nume(Student v[], int nr_studenti);
    void sort_dupa_medie(Student v[], int nr_studenti);
    static Student* restanta(Student v[], int nr_studenti);

    void afisare();

    ~Student(){
        delete [] this -> nume;
        delete [] this -> prenume; // “DA, trebuie eu sa eliberez memoria”
    }
};



Student :: Carnet_de_note &Student :: Carnet_de_note::operator=(const Student :: Carnet_de_note& materie){
    this -> medie = materie.medie;
    this -> nr_credite = materie.nr_credite;
    return *this;
};

Student Student :: operator=(const Student& student){
    this -> nume = new char[strlen(student.nume + 1)];
    this -> prenume = new char[strlen(student.prenume + 1)];
    strcpy(this -> nume, student.nume);
    strcpy(this -> prenume, student.prenume);
    this -> nr_materii = student.nr_materii;
    for(int i = 0; i < this -> nr_materii; i++)
        this -> materii[i] = student.materii[i];
    return *this;
}

istream &operator>>(istream &is, Student :: Carnet_de_note &materie){
    cout<<"\nMedie: ";
    is >> materie.medie;
    cout<<"\nNumar de credite: ";
    is >> materie.nr_credite;
    return is;
}



istream &operator>>(istream &is, Student &student){
    char cuv1[30], cuv2[30];
    cout << "\nNume: ";
    is >> cuv1;
    cout << "\nPrenume: ";
    is>>cuv2;
    student.nume = new char[strlen(cuv1)];
    strcpy(student.nume,cuv1);
    student.prenume = new char[strlen(cuv2)];
    strcpy(student.prenume,cuv2);
    cout << "\nNumar de materii: ";
    is >> student.nr_materii;
    for(int i = 0; i < student.nr_materii; i++){
        cout << "\nMateria " << i + 1 << ": ";
        cin >> student.materii[i];
    }
    return is;

}
void Student :: afisare(){
    cout << "\n";
    cout << this -> nume;
    cout << " ";
    cout << this -> prenume;
}


float Student :: calcul_medie_generala(){ // calculul mediei generale a unui student
    float med_gen = 0;
    int n = this -> nr_materii;
    for(int i = 0; i < n; i++){
        med_gen += materii[i].intoarce_medie();
    }
    med_gen /= n;
    this -> medie_generala = med_gen;
    return med_gen;
}



Student * Student :: sort_dupa_nume(Student *v, int nr_studenti){  // sortarea alfabetica
  int i,j;
  Student aux;
  for( i = 1; i < nr_studenti;i++){
      j = i ;
      while(j > 0 && ((strcmp(v[j].nume, v[j - 1].nume) == 0 || strcmp(v[j].prenume, v[j - 1].prenume) < 0) || (strcmp(v[j].nume, v[j - 1].nume) < 0))) {
          aux = v[j];
          v[j] = v[j - 1];
          v[j - 1] = aux;
          j--;
      }
  }
  return v;
}
void Student  ::  sort_dupa_medie(Student *v, int nr_studenti){ // sortarea dupa medie generala
    int i,j;
    Student aux;
    for(i = 1;  i < nr_studenti; i++){
        j = i;
        while(v[j - 1].medie_generala < v[j].medie_generala){
            aux = v[j];
            v[j] = v[j - 1];
            v[j - 1] = aux;
            j--;
        }

    }
    for(i = 0; i < 5 && i < nr_studenti; i++) // afisarea primilor 5 bursieri (sau a tuturor bursierilor in cazul in care sunt mai putin de 5 studenti)
        cout<<'\n'<<v[i].intoarce_nume()<<' '<<v[i].intoarce_prenume();

}

Student * Student :: restanta(Student *v, int nr_studenti){
    Student *restantieri;
    int nr_restantieri = 0, max_crd_materie = 0,i,j, credit;
    restantieri = new Student[nr_studenti];
    for(i = 0; i < nr_studenti; i++){
        for(j = 0; j < v[i].nr_materii; j++){
            credit = v[i].materii[j].intoarce_nr_credite();
            if(credit > max_crd_materie){
                max_crd_materie = credit;
                nr_restantieri = 0;
            }
            if(credit == max_crd_materie && restantieri[i].materii[j].intoarce_medie() < 5)
                restantieri[nr_restantieri++] = v[i];
        }
    }
    return restantieri;

}

int main(){
    int nr_studenti,i;
    Student *studenti, *restantieri, *alfabetizati;
    cout << "Numarul de studenti :  ";
    cin >> nr_studenti;
    studenti = new Student[nr_studenti];
    for(i = 0;  i < nr_studenti; i++){
        cin >> studenti[i];
        cout <<"\n"<< "Medie generala: " << studenti[i].calcul_medie_generala()<<'\n';

    }
    restantieri = new Student[nr_studenti];
    restantieri = Student :: restanta(studenti, nr_studenti);
    cout <<"\n\nRESTANTIERI :";
    for(i = 0; i < nr_studenti; i++)
        restantieri[i].afisare();
    cout<<"\n\nBURSIERI:";
    studenti -> sort_dupa_medie(studenti, nr_studenti);

    alfabetizati = new Student[nr_studenti];
    alfabetizati = Student :: sort_dupa_nume(studenti, nr_studenti);

    cout<<"\n\nORDONATI ALFABETIC:";
    for(i = 0; i < nr_studenti; i++)
        alfabetizati[i].afisare();
    delete [] studenti;
    delete [] restantieri;
    //delete[]alfabetizati - da crash
    return 0;
}
