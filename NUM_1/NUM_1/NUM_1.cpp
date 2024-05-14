#include <iostream>

class Permutation {
 private:
  int* num;
  int sz;

 public:
  // конструкторы
  Permutation(int n) : sz(n) {
    num = new int[sz];
    for (int i = 0; i < sz; i++) {
      num[i] = i + 1;
    }
  }

  Permutation(const Permutation& other) : sz(other.sz) {
    num = new int[sz];
    for (int i = 0; i < sz; i++) {
      num[i] = other.num[i];
    }
  }

  Permutation(int n, int* first) : sz(n) {
    num = new int[sz];
    for (int i = 0; i < sz; i++) {
      num[i] = first[i];
    }
  }

  Permutation(unsigned int n) : sz(n) {
    num = new int[sz];
    for (int i = 0; i < sz; i++) {
      num[i] = i;
    }
  }

  ~Permutation() { delete[] num; }

  // вывод текста
  void print() {
    for (int i = 0; i < sz; i++) {
      std::cout << num[i] << " ";
    }
    std::cout << '\n';
  }

  // смена местами элементов
  void Swap(int& first, int& second) {
    int tmp = first;
    first = second;
    second = tmp;
  }

  // поиск след. перестановки
  void Next_permutation() {
    int i = sz - 1;
    // ищем самый правый элемент, который меньше следующего за ним элемента.
    while (i > 0 && num[i - 1] >= num[i]) {
      i--;
    }
    // текущая перестановка является последней в лексикографическом порядке
    if (i == 0) {
      std::reverse(num, num + sz);
      return;
    }
    // В противном случае, начиная с последнего элемента, ищем самый правый
    // элемент, который больше элемента
    int j = sz - 1;
    while (num[j] <= num[i - 1]) {
      j--;
    }
    std::swap(num[i - 1], num[j]);
    std::reverse(num + i, num + sz);
  }

  // поиск предыдущей перестановки
  void Previous_permutation() {
    int i = sz - 1;
    // ищем самый правый элемент, который больше следующего за ним элемента
    while (i > 0 && num[i - 1] <= num[i]) {
      i--;
    }
    //  текущая перестановка является первой в лексикографическом порядке
    if (i == 0) {
      std::reverse(num, num + sz);
      return;
    }
    // начиная с последнего элемента, ищем самый правый элемент, который меньше
    // элемента
    int j = sz - 1;
    while (num[j] >= num[i - 1]) {
      j--;
    }
    std::swap(num[i - 1], num[j]);
    std::reverse(num + i, num + sz);
  }

  Permutation& operator=(const Permutation& other) {
    if (this != &other) {
      delete[] num;
      sz = other.sz;
      num = new int[sz];
      for (int i = 0; i < sz; i++) {
        num[i] = other.num[i];
      }
    }
    return *this;
  }

  Permutation operator*(const Permutation& other) {
    if (sz == other.sz) {
      int* res = new int[sz];
      for (int i = 0; i < sz; i++) {
        res[i] = other.num[num[i] - 1];
      }
      Permutation composed(sz, res);
      delete[] res;
      return composed;
    } else {
      std::cout << "Different sizes\n";
      return other;  // Возвращаем вторую перестановку в случае ошибки
    }
  }

  bool operator<(const Permutation& other) const {
    if (this->sz != other.sz) {
      return false;
    }
    for (int i = 0; i < sz; i++) {
      if (num[i] < other.num[i]) {
        return true;
      } else if (num[i] > other.num[i]) {
        return false;
      }
    }
    return false;
  }

  bool operator==(const Permutation& other) const {
    if (this->sz != other.sz) {
      return false;
    }
    for (int i = 0; i < sz; i++) {
      if (num[i] != other.num[i]) {
        return false;
      }
    }
    return true;
  }

  bool operator!=(const Permutation& other) const {
    if (this->sz != other.sz) {
      return false;
    }
    return !(*this == other);
  }

  bool operator>(const Permutation& other) const {
    if (this->sz != other.sz) {
      return false;
    }
    return other < *this;
  }

  bool operator<=(const Permutation& other) const {
    if (this->sz != other.sz) {
      return false;
    }
    return !(other < *this);
  }

  bool operator>=(const Permutation& other) const {
    if (this->sz != other.sz) {
      return false;
    }
    return !(*this < other);
  }

  Permutation& operator++() {
    Next_permutation();
    return *this;
  }

  Permutation operator++(int) {
    Permutation tmp(this->sz, this->num);
    Next_permutation();
    return tmp;
  }

  Permutation& operator--() {
    Previous_permutation();
    return *this;
  }

  Permutation operator--(int) {
    Permutation tmp(this->sz, this->num);
    Previous_permutation();
    return tmp;
  }
};

int main() {
  // Установка локали на русскую
  setlocale(LC_ALL, "Russian");

  int n;
  std::cout << "Количество элементов first:" << std::endl;
  std::cin >> n;
  int* first;
  first = new int[n];
  std::cout << "Введите элементы first:" << std::endl;
  for (int i = 0; i < n; i++) {
    std::cin >> first[i];
  }
  Permutation perm(n, first);
  perm.print();
  // perm++;
  std::cout << "Следующая перестановка: ";
  perm.print();
  std::cout << "Предыдущая перестановка: ";
  perm--;
  perm.print();

  // Запрос размера и элементов перестановки second
  int m;
  std::cout << "Введите количество элементов second:" << std::endl;
  std::cin >> m;
  int* b_elements = new int[m];
  std::cout << "Введите элементы second:" << std::endl;
  for (int i = 0; i < m; ++i) {
    std::cin >> b_elements[i];
  }
  Permutation second(m, b_elements);

  if (perm == second) {
    std::cout << "OK = \n";
  } else if (perm < second) {
    std::cout << "OK < \n";
  } else if (perm > second) {
    std::cout << "OK > \n";
  }
  std::cout << "Вывод second: ";
  second.print();

  // Вывод композиции перестановок
  if (m == n) {
    Permutation composed = perm * second;
    std::cout << "Сложная перестановка: ";
    composed.print();
  }

  delete[] first;
  delete[] b_elements;

  return 0;
}
