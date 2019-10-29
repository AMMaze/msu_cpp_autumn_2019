using uint = unsigned int;

class Matrix {
    uint rows, cols;
    int *matrix;

    class Row {
        uint cols;
        int *row;
    public:
        Row(uint c, int *r);
        int& operator[] (uint i);
    };

public:
    Matrix(uint r, uint c);
    Matrix(uint r, uint c, int *m);
    ~Matrix();

    bool operator== (Matrix &matr);
    bool operator!= (Matrix &matr);
    Matrix& operator*= (int n);
    //friend Matrix& operator*= (Matrix& m, int n);

    uint getRows() const;
    uint getColumns() const;

    Row operator[] (uint i);
};
