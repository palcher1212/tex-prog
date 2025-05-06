#include <iostream>
#include <stdexcept>
using namespace std;

class Matrix;

class Vector {
private:
    double* data;
    int size;
    int id;
    static int counter;

public:
    Vector(int size = 0) : size(size), data(size ? new double[size] : nullptr), id(++counter) {
        cout << "Создан вектор #" << id << " размерности " << size << endl;
    }

    Vector(const Vector& v) : size(v.size), data(size ? new double[size] : nullptr), id(++counter) {
        cout << "Скопирован вектор #" << v.id << " в #" << id << endl;
        for (int i = 0; i < size; i++)
            data[i] = v.data[i];
    }

    ~Vector() {
        cout << "Уничтожен вектор #" << id << endl;
        delete[] data;
        counter--;
    }

    double& operator[](int i) {
        if (i < 0 || i >= size) throw out_of_range("Индекс выходит за границы вектора");
        return data[i];
    }

    const double& operator[](int i) const {
        if (i < 0 || i >= size) throw out_of_range("Индекс выходит за границы вектора");
        return data[i];
    }

    Vector& operator=(const Vector& v) {
        cout << "Присваивание вектора #" << v.id << " вектору #" << id << endl;
        if (this != &v) {
            if (size != v.size) {
                delete[] data;
                size = v.size;
                data = size ? new double[size] : nullptr;
            }
            for (int i = 0; i < size; i++)
                data[i] = v.data[i];
        }
        return *this;
    }

    Vector operator+(const Vector& v) const {
        if (size != v.size) {
            throw invalid_argument("Размеры векторов не совпадают для сложения");
        }
        cout << "Сложение векторов #" << id << " и #" << v.id << endl;
        Vector res(size);
        for (int i = 0; i < size; i++)
            res[i] = data[i] + v[i];
        return res;
    }

    Vector operator-(const Vector& v) const {
        if (size != v.size) {
            throw invalid_argument("Размеры векторов не совпадают для вычитания");
        }
        cout << "Вычитание векторов #" << id << " и #" << v.id << endl;
        Vector res(size);
        for (int i = 0; i < size; i++)
            res[i] = data[i] - v[i];
        return res;
    }

    Vector operator-() const {
        cout << "Унарный минус для вектора #" << id << endl;
        Vector res(size);
        for (int i = 0; i < size; i++)
            res[i] = -data[i];
        return res;
    }

    double operator*(const Vector& v) const {
        if (size != v.size) {
            throw invalid_argument("Размеры векторов не совпадают для скалярного произведения");
        }
        cout << "Скалярное произведение векторов #" << id << " и #" << v.id << endl;
        double sum = 0;
        for (int i = 0; i < size; i++)
            sum += data[i] * v[i];
        return sum;
    }

    Vector operator*(double k) const {
        cout << "Умножение вектора #" << id << " на скаляр " << k << endl;
        Vector res(size);
        for (int i = 0; i < size; i++)
            res[i] = k * data[i];
        return res;
    }

    ostream& print(ostream& os) const {
        os << "Вектор #" << id << ": [";
        for (int i = 0; i < size; i++) {
            os << data[i];
            if (i < size - 1) os << ", ";
        }
        os << "]";
        return os;
    }

    istream& input(istream& is) {
        cout << "Введите " << size << " элементов вектора #" << id << ": ";
        for (int i = 0; i < size; i++)
            is >> data[i];
        return is;
    }

    friend class Matrix;
};

class Matrix {
private:
    double** data;
    int size;
    int id;
    static int counter;

public:
    Matrix(int size = 0) : size(size), data(size ? new double*[size] : nullptr), id(++counter) {
        cout << "Создана матрица #" << id << " размерности " << size << endl;
        for (int i = 0; i < size; i++)
            data[i] = new double[size];
    }

    Matrix(const Matrix& m) : size(m.size), data(size ? new double*[size] : nullptr), id(++counter) {
        cout << "Скопирована матрица #" << m.id << " в #" << id << endl;
        for (int i = 0; i < size; i++) {
            data[i] = new double[size];
            for (int j = 0; j < size; j++)
                data[i][j] = m.data[i][j];
        }
    }

    ~Matrix() {
        cout << "Уничтожена матрица #" << id << endl;
        for (int i = 0; i < size; i++)
            delete[] data[i];
        delete[] data;
        counter--;
    }

    double* operator[](int i) {
        if (i < 0 || i >= size) throw out_of_range("Индекс строки выходит за границы матрицы");
        return data[i];
    }

    const double* operator[](int i) const {
        if (i < 0 || i >= size) throw out_of_range("Индекс строки выходит за границы матрицы");
        return data[i];
    }

    Matrix& operator=(const Matrix& m) {
        cout << "Присваивание матрицы #" << m.id << " матрице #" << id << endl;
        if (this != &m) {
            if (size != m.size) {
                for (int i = 0; i < size; i++)
                    delete[] data[i];
                delete[] data;
                size = m.size;
                data = size ? new double*[size] : nullptr;
                for (int i = 0; i < size; i++)
                    data[i] = new double[size];
            }
            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                    data[i][j] = m.data[i][j];
        }
        return *this;
    }

    Matrix operator+(const Matrix& m) const {
        if (size != m.size) {
            throw invalid_argument("Размеры матриц не совпадают для сложения");
        }
        cout << "Сложение матриц #" << id << " и #" << m.id << endl;
        Matrix res(size);
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                res[i][j] = data[i][j] + m[i][j];
        return res;
    }

    Matrix operator-(const Matrix& m) const {
        if (size != m.size) {
            throw invalid_argument("Размеры матриц не совпадают для вычитания");
        }
        cout << "Вычитание матриц #" << id << " и #" << m.id << endl;
        Matrix res(size);
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                res[i][j] = data[i][j] - m[i][j];
        return res;
    }

    Matrix operator-() const {
        cout << "Унарный минус для матрицы #" << id << endl;
        Matrix res(size);
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                res[i][j] = -data[i][j];
        return res;
    }

    Matrix operator*(const Matrix& m) const {
        if (size != m.size) {
            throw invalid_argument("Размеры матриц не совпадают для умножения");
        }
        cout << "Умножение матриц #" << id << " и #" << m.id << endl;
        Matrix res(size);
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++) {
                res[i][j] = 0;
                for (int k = 0; k < size; k++)
                    res[i][j] += data[i][k] * m[k][j];
            }
        return res;
    }

    Vector operator*(const Vector& v) const {
        if (size != v.size) {
            throw invalid_argument("Размеры матрицы и вектора не совпадают для умножения");
        }
        cout << "Умножение матрицы #" << id << " на вектор #" << v.id << endl;
        Vector res(size);
        for (int i = 0; i < size; i++) {
            res[i] = 0;
            for (int j = 0; j < size; j++)
                res[i] += data[i][j] * v[j];
        }
        return res;
    }

    Matrix operator*(double k) const {
        cout << "Умножение матрицы #" << id << " на скаляр " << k << endl;
        Matrix res(size);
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                res[i][j] = k * data[i][j];
        return res;
    }

    ostream& print(ostream& os) const {
        os << "Матрица #" << id << ":\n";
        for (int i = 0; i < size; i++) {
            os << "[";
            for (int j = 0; j < size; j++) {
                os << data[i][j];
                if (j < size - 1) os << ", ";
            }
            os << "]\n";
        }
        return os;
    }

    istream& input(istream& is) {
        cout << "Введите " << size * size << " элементов матрицы #" << id << ":\n";
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                is >> data[i][j];
        return is;
    }
};

int Vector::counter = 0;
int Matrix::counter = 0;

// перегрузка 
ostream& operator<<(ostream& os, const Vector& v) {
    return v.print(os);
}

istream& operator>>(istream& is, Vector& v) {
    return v.input(is);
}

ostream& operator<<(ostream& os, const Matrix& m) {
    return m.print(os);
}

istream& operator>>(istream& is, Matrix& m) {
    return m.input(is);
}

int main() {
    try {
        cout << "=== Демонстрация работы с векторами ===" << endl;
        Vector v1(2), v2(2), v3(2);
        cin >> v1 >> v2;

        cout << "\nОперации с векторами:" << endl;
        v3 = v1 + v2;
        cout << "v1 + v2 = " << v3 << endl;

        v3 = v1 - v2;
        cout << "v1 - v2 = " << v3 << endl;

        v3 = -v1;
        cout << "-v1 = " << v3 << endl;

        double scalar = v1 * v2;
        cout << "v1 * v2 = " << scalar << endl;

        v3 = v1 * 2.5;
        cout << "v1 * 2.5 = " << v3 << endl;

        cout << "\n=== Демонстрация работы с матрицами ===" << endl;
        Matrix m1(2), m2(2), m3(2);
        cin >> m1 >> m2;

        cout << "\nОперации с матрицами:" << endl;
        m3 = m1 + m2;
        cout << "m1 + m2 =\n" << m3 << endl;

        m3 = m1 - m2;
        cout << "m1 - m2 =\n" << m3 << endl;

        m3 = -m1;
        cout << "-m1 =\n" << m3 << endl;

        m3 = m1 * m2;
        cout << "m1 * m2 =\n" << m3 << endl;

        m3 = m1 * 3.0;
        cout << "m1 * 3.0 =\n" << m3 << endl;

        cout << "\nУмножение матрицы на вектор:" << endl;
        v3 = m1 * v1;
        cout << "m1 * v1 = " << v3 << endl;

        // Тест с разными размерностями
        cout << "\n=== Тест с разными размерностями ===" << endl;
        Vector v4(3);
        Matrix m4(3);
        try {
            Vector test = m1 * v4; // Должно вызвать ошибку
        } catch (const invalid_argument& e) {
            cout << "Ошибка перехвачена: " << e.what() << endl;
        }

    } catch (const exception& e) {
        cerr << "Произошла ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}
