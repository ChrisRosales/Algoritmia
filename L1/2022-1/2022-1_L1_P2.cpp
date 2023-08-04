#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#define FILE_NAME "Lab1_P2_data.txt"
#define MAX_CURSOS 20
#define MIN_CREDITOS 12
using namespace std;
typedef struct {
    int id;
    int creditos;
    int horario;
    int sesionTeoria;
    int horaInicioTeoria;
    int horaFinalTeoria;
    int sesionPractica;
    int horaInicioPractica;
    int horaFinalPractica;
    int evaluacion;
} Curso;

void leerDatos(Curso **cursos, int *L, int *cant);
bool horarioValido(int *cromosoma, Curso *cursos, int cantCurso, int *creditos, int L);
bool parCursoValido(Curso *cursos, int i, int j);
bool semanaEvaluacion(Curso *cursos, int i, int j);
bool validoHoraGeneral(int inicioI, int finI, int inicioJ, int finJ);
void CargarCromosoma(int *cromosoma, int size, int num);
int main(){
	 Curso *cursos;
    int L, cantCursos;
    leerDatos(&cursos, &L, &cantCursos);
    // Verificación de la lectura de los datos
    //    std::cout << "L: " << L << " C: " << cantCursos << "\n";
    //    for (int i = 0; i < cantCursos; i++) {
    //        std::cout << cursos[i].id
    //                << " " << cursos[i].creditos
    //                << " " << cursos[i].horario
    //                << " " << cursos[i].sesionTeoria
    //                << " " << cursos[i].horaInicioTeoria
    //                << " " << cursos[i].horaFinalTeoria
    //                << " " << cursos[i].sesionPractica
    //                << " " << cursos[i].horaInicioPractica
    //                << " " << cursos[i].horaFinalPractica
    //                << " " << cursos[i].evaluacion << "\n";
    //    }

    int combinaciones = pow(2, cantCursos),
            creditos = 0,
            creditosMaximos = 0,
            combinacionFinal,
            cromosoma[cantCursos];


    for (int i = 1; i < combinaciones; i++) {
        CargarCromosoma(cromosoma, cantCursos, i);
        if (!horarioValido(cromosoma, cursos, cantCursos, &creditos, L)) continue;
        if (creditos > creditosMaximos) {
            combinacionFinal = i;
            creditosMaximos = creditos;
        }
    }
    CargarCromosoma(cromosoma, cantCursos, combinacionFinal);
    for (int i = 0; i < cantCursos; i++) {
        if (cromosoma[i]) {
            std::cout << std::setfill('0') << std::setw(6) << cursos[i].id
                    << "-" << std::setfill('0') << std::setw(4) << cursos[i].horario << "\n";
        }
    }
    std::cout << "Creditos finales: " << creditosMaximos << "\n";

    // Todas las soluciones posibles
    std::cout << std::setfill('*') << std::setw(30) << '*';
    std::cout << "\nTodas las soluciones posibles\n";
    std::cout << std::setfill('*') << std::setw(30) << '*' << std::endl;

    int casos = 1;
    for (int i = 1; i < combinaciones; i++) {
        CargarCromosoma(cromosoma, cantCursos, i);
        if (!horarioValido(cromosoma, cursos, cantCursos, &creditos, L)) continue;
        if (creditos == creditosMaximos) {
            std::cout << "N° de casos: " << casos++ << "\n";
            for (int j = 0; j < cantCursos; j++) {
                if (cromosoma[j]) {
                    std::cout << std::setfill('0') << std::setw(6) << cursos[j].id << "-"
                            << std::setfill('0') << std::setw(4) << cursos[j].horario << "\n";
                }
            }
            std::cout << std::setfill('-') << std::setw(30) << '-' << std::endl;
        }
    }
	return 0;
}

/**
 * Lectura de los datos
 * @param cursos: almacenamiento de la función
 * @param L: maximo cantidad de creditos
 * @param cant: cantidad de cursos del archivo
 */
void leerDatos(Curso **cursos, int *L, int *cant) {
    std::ifstream archivo(FILE_NAME, std::ios::in);
    if (!archivo) {
        std::cout << "No se pudo abrir el archivo " << FILE_NAME << "para su lectura\n";
        exit(1);
    }
    *cursos = new Curso[MAX_CURSOS];
    int i = 0;
    archivo >> *L;
    while (!archivo.eof()) {
        archivo >> (*cursos)[i].id
                >> (*cursos)[i].creditos
                >> (*cursos)[i].horario
                >> (*cursos)[i].sesionTeoria
                >> (*cursos)[i].horaInicioTeoria
                >> (*cursos)[i].horaFinalTeoria
                >> (*cursos)[i].sesionPractica
                >> (*cursos)[i].horaInicioPractica
                >> (*cursos)[i].horaFinalPractica
                >> (*cursos)[i].evaluacion;
        i++;
    }
    *cant = i;
    archivo.close();
}

bool horarioValido(int *cromosoma, Curso *cursos, int cantCurso, int *creditos, int L) {
    int indexCurso[cantCurso], index = 0;
    *creditos = 0;
    for (int i = 0; i < cantCurso; i++) {
        if (!cromosoma[i]) continue;
        (*creditos) += cursos[i].creditos;
        // aprovecharemos este ciclo while, para agregar llenar el arreglo indexCurso
        // Con los cursos posibles
        indexCurso[index] = cursos[i].id;
        index++;
    }
    // validamos la cantidad de crédtios, en caso no este dentro de límite
    // no tenemos necesidad de seguir analizando
    if (*creditos < MIN_CREDITOS || *creditos > L)
        return false;
    for (int i = 0; i < index; i++) {
        for (int j = 0; j < index; j++) {
            // se repitio un curso, por lo que se retorna falso
            if (indexCurso[i] == indexCurso[j] && i != j)
                return false;
        }
    }
    // Ahora tenemos que validar si no existen cruses entre los horarios
    // Para esto se tiene que verificar cada curso escogido; con los demás cursos posibles
    for (int i = 0; i < cantCurso; i++) {
        for (int j = 0; j < cantCurso; j++) {
            // validamos que los 2 cursos se pueden llevar
            // No estoy analizando el mismo curso
            // y analizamos si es posible llevar dicho par de cursos
            if (cromosoma[i] && cromosoma[j] && i != j && !parCursoValido(cursos, i, j)) {
                return false;
            }
        }
    }
    return true;
}

bool parCursoValido(Curso *cursos, int i, int j) {

    // Horario I
    int inicioTeoriaI = cursos[i].horaInicioTeoria,
            finalTeoriaI = cursos[i].horaFinalTeoria;
    int inicioPracticaI = cursos[i].horaInicioPractica,
            finalPracticaI = cursos[i].horaFinalPractica;
    // Horario J
    int inicioTeoriaJ = cursos[j].horaInicioTeoria,
            finalTeoriaJ = cursos[j].horaFinalTeoria;
    int inicioPracticaJ = cursos[j].horaInicioPractica,
            finalPracticaJ = cursos[j].horaFinalPractica;

    // analicemos la parte más simple; todas las semanas si o si se tiene que evaluar
    // el las sesionse teóricas
    if (cursos[i].sesionTeoria == cursos[j].sesionTeoria &&
            !validoHoraGeneral(inicioTeoriaI, finalTeoriaI, inicioTeoriaJ, finalTeoriaJ)) {
        return false;
    }
    // No todas las semanas tenemos sesiones teoricas
    // por lo que primero evaluamos si en dichas semanas vamos a tener evaluaciones
    if (semanaEvaluacion(cursos, i, j)) {
        // Aqui vamos a tener 3 posibles casos
        // evaluamos Teoria1 con practica 2
        // practica 1 con teoria2
        // pracita1 con practica2

        // Teoria I con Practica J
        if (cursos[i].sesionTeoria == cursos[j].sesionPractica &&
                !validoHoraGeneral(inicioTeoriaI, finalTeoriaI, inicioPracticaJ, finalPracticaJ))
            return false;
        // Practica I con Teoria J
        if (cursos[i].sesionPractica == cursos[j].sesionTeoria &&
                !validoHoraGeneral(inicioPracticaI, finalPracticaI, inicioTeoriaJ, finalTeoriaJ))
            return false;
        // Practica I con Practica J
        if (cursos[i].sesionPractica == cursos[j].sesionPractica &&
                !validoHoraGeneral(inicioPracticaI, finalPracticaI, inicioPracticaJ, finalPracticaJ))
            return false;
    }
    return true;
}

bool semanaEvaluacion(Curso *cursos, int i, int j) {
    // Un horario, puede que tenga evaluaciones en la semana par
    // en la semana impar o en ambas
    // y justamente eso es lo que estamos evaluando
    return cursos[i].evaluacion == cursos[j].evaluacion || cursos[i].evaluacion == 3 || cursos[j].evaluacion == 3;
}

bool validoHoraGeneral(int inicioI, int finI, int inicioJ, int finJ) {
    if ((inicioI >= finJ) || (finI <= inicioJ)) return true;
    return false;
}
void CargarCromosoma(int *cromosoma, int size, int num) {
    int i = size - 1;
    while (num != 0) {
        cromosoma[i] = num % 2;
        num /= 2;
        i--;
    }
    for (int j = 0; j <= i; j++) {
        cromosoma[j] = 0;
    }
}

