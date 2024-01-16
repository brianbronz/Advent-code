#include "../Allreference.h"

struct feature{
    vector<long double> position;
    vector<long double> speed;
};

long double minValue = 200000000000000;
long double maxValue = 400000000000000;
//long double minValue = 7;
//long double maxValue = 27;
vector<struct feature*> listFeatures;
int readFiles(istream & input, const char * argv){
    string block;
    while(getline(input, block)){
        int positionSymbol = block.find('@');
        string position = block.substr(0, positionSymbol - 1);
        string velocity = block.substr(positionSymbol + 2);
        vector<long double> first;
        vector<long double> second;
        for(int i = 0; i < 3; i++){
            if(position.find(',') != string::npos){
                first.push_back(stoll(position.substr(0, position.find(','))));
                second.push_back(stoll(velocity.substr(0, velocity.find(','))));
            } else {
                first.push_back(stoll(position));
                second.push_back(stoll(velocity));
            }
            position = position.substr(position.find(',') + 1);
            velocity = velocity.substr(velocity.find(',') + 1);
        }
        struct feature * newFeature = new(feature);
        newFeature->position = first;
        newFeature->speed = second;
        listFeatures.push_back(newFeature);
    } 
    return -1;
}


long double isIntersect(struct feature * a, struct feature * b){
    long double ax, ay, az, firstvx, avy, avz;
    long double bx, by, bz, secondvx, secondvy, secondvz;
    ax = a->position[0];
    ay = a->position[1];
    az = a->position[2];
    firstvx = a->speed[0];
    avy = a->speed[1];
    avz = a->speed[2];
    bx = b->position[0];
    by = b->position[1];
    bz = b->position[2];
    secondvx = b->speed[0];
    secondvy = b->speed[1];
    secondvz = b->speed[2];
    //parametric
    long double time = (secondvy * (bx - ax) - secondvx *(by - ay)) / (firstvx * secondvy - secondvx * avy);
    if(time < 0){return 0;}
    long double space = (ax + firstvx * time - bx) / secondvx;
    if(space < 0){return 0;}
    long double x = ax + firstvx * time;
    long double y = ay + avy * time;
    if (x >= double(minValue) && x <= double(maxValue) && y >= double(minValue) && y <= double(maxValue)){
        return 1; 
    }
    return 0;
}

//solution part 2: 695832176624149
long double check(){
    long double sum = 0;
    for(int i = 0; i < listFeatures.size() - 1; i++){
        for(int j = i + 1; j < listFeatures.size(); j++){
            sum += isIntersect(listFeatures[i], listFeatures[j]);
        }
    }
    cout << sum << endl;
    return sum;
}

long double determinant(long double mat[6][6], int N){
    long double det = 1;
    // Gauss elimination
    for (int i = 0; i < N; i++) {
        //Highest value of the row
        int maxRowIndex = i;
        for (int j = i + 1; j < N; j++) {
            if (abs(mat[j][i]) > abs(mat[maxRowIndex][i])) {
                maxRowIndex = j;
            }
        }

        // Swap the rows
        if (maxRowIndex != i) {
            for (int k = 0; k < N; k++) {
                swap(mat[i][k], mat[maxRowIndex][k]);
            }
            det = -det;
        }

        // obtain an upper matrix
        for (int j = i + 1; j < N; j++) {
            long double ratio = mat[j][i] / mat[i][i];
            for (int k = i; k < N; k++) {
                mat[j][k] -= ratio * mat[i][k];
            }
        }
        det *= mat[i][i];
    }

    return det;
}

long double determinant(long double mat[5][5], int N){
    long double det = 1;
    // Gauss elimination
    for (int i = 0; i < N; i++) {
        //Highest value of the row
        int maxRowIndex = i;
        for (int j = i + 1; j < N; j++) {
            if (abs(mat[j][i]) > abs(mat[maxRowIndex][i])) {
                maxRowIndex = j;
            }
        }

        // Swap the rows
        if (maxRowIndex != i) {
            for (int k = 0; k < N; k++) {
                swap(mat[i][k], mat[maxRowIndex][k]);
            }
            det = -det;
        }

        // obtain an upper matrix
        for (int j = i + 1; j < N; j++) {
            long double ratio = mat[j][i] / mat[i][i];
            for (int k = i; k < N; k++) {
                mat[j][k] -= ratio * mat[i][k];
            }
        }
        det *= mat[i][i];
    }

    return det;
}

long double subDeterminant(long double mat[6][6], int row, int col) {
    long double subMat[5][5];
    int subi = 0, subj = 0;

    for (int i = 0; i < 6; i++) {
        if (i != row) {
            subj = 0;
            for (int j = 0; j < 6; j++) {
                if (j != col) {
                    subMat[subi][subj] = mat[i][j];
                    subj++;
                }
            }
            subi++;
        }
    }

    long double subDet = determinant(subMat, 6 - 1);
    return subDet;
}

long double adjoint(long double matrix[6][6], long double cofactor[6][6]){
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            int sign = ((i + j) % 2 == 0) ? 1 : -1;
            long double subDet = subDeterminant(matrix, i, j);
            cofactor[j][i] = sign * subDet;
        }
    }
}

void calculateInverse(long double matrix[6][6], long double inverse[6][6]){
    //find the determinant
    long double det = determinant(matrix, 6);
    cout << det << endl;
    //adjacent matrix
    long double cofactor[6][6];
    adjoint(matrix, cofactor);
    long double adj[6][6];
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            adj[i][j] = cofactor[j][i];
        }
    }
    //inverse
    for (int i =0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            inverse[i][j] = adj[i][j] / det;
        }
    }
}

void multiplyMatrixVector(long double mat[6][6], vector<long double> vec, long double result[6]) {
    for (int i = 0; i < 6; i++) {
        result[i] = 0;
        for (int j = 0; j < 6; j++) {
            result[i] += mat[i][j] * vec[j];
        }
    }
    int64_t sum = int64_t(round(result[0]) + round(result[1]) + round(result[2]));

    cout << "Somma arrotondata: " << sum << endl;
}

long double secondPart(){
    //need to find a single position, which collide with every hailstone
    //Therefore we need to consider that for each stone, A = first + Av*t, our ray (position + QT)
    //should match a t value
    //we consider also the z coordinate, having in this way 3 equations:
    // firstx + firstvx*t = x + Qx*t
    // firsty + Avy*t = y + Qy*t
    // firstz + Avz*t = Pz + Qz*t
    //We choose the first three stones such that we have nine equations
    vector<long double> firstPos;
    vector<long double> firstVel;
    firstPos.push_back(listFeatures[0]->position[0]);
    firstPos.push_back(listFeatures[0]->position[1]);
    firstPos.push_back(listFeatures[0]->position[2]);
    firstVel.push_back(listFeatures[0]->speed[0]);
    firstVel.push_back(listFeatures[0]->speed[1]);
    firstVel.push_back(listFeatures[0]->speed[2]);
    vector<long double> secondPos;
    vector<long double> secondVel;
    secondPos.push_back(listFeatures[1]->position[0]);
    secondPos.push_back(listFeatures[1]->position[1]);
    secondPos.push_back(listFeatures[1]->position[2]);
    secondVel.push_back(listFeatures[1]->speed[0]);
    secondVel.push_back(listFeatures[1]->speed[1]);
    secondVel.push_back(listFeatures[1]->speed[2]);
    vector<long double> thirdPos;
    vector<long double> thirdVel;
    thirdPos.push_back(listFeatures[2]->position[0]);
    thirdPos.push_back(listFeatures[2]->position[1]);
    thirdPos.push_back(listFeatures[2]->position[2]);
    thirdVel.push_back(listFeatures[2]->speed[0]);
    thirdVel.push_back(listFeatures[2]->speed[1]);
    thirdVel.push_back(listFeatures[2]->speed[2]);
    //We can reduce our problems in the following way:
    // (x - firstX) / (firstVx - Qx) = (y - firstY) / (firstVy - Qy) = (z - firstz) / (firstVz - Qz)
    //  ... 
    //the same stuff with the second and third vector

    //Then we rearrange the x/y pairing:

    // x * Avy - x * Qy - firstX * Avy + firstVx * Qy = y * firstVx - y * Qx - firstY * firstVx + firstY * Qx
    // (x * Qy - y * Qx) = (x * Avy - y * firstvx) + (firsty * firstvx - firstx * Avy) + (firstx * Qy - firsty * Qx)   {Equation 1}
    // (x * Qy - y * Qx) = (x * secondvy - y * secondvx) + (secondy * secondvx - secondx * secondvy) + (secondx * Qy - secondy * Qx)   {Equation 2}
    // We do the same also for z/x and y/z
    // Setting equations 1 and 2 equal to each other (to cancel out the common (x * Qy - y * Qx) term) gives us:
    // [firstvy - secondvy]x - [firstvx - secondvx]y - [firsty - secondy]Qx + [firstx - secondx]Qy = (secondy * secondvx - secondx * secondvy) - (firsty * firstvx - firstx * firstvy)
    //
    // We can encounter other similar equations such that we can define a matrix and a vector
    // For this code, we'll write it in matrix/vector notation:
    const int rows = 6;
    const int columns = 6;
    long double matrix[rows][columns] = {
        { firstVel[1] - secondVel[1],  secondVel[0] - firstVel[0],          0.0,  secondPos[1] - firstPos[1],  firstPos[0] - secondPos[0],          0.0 },
        { firstVel[1] - thirdVel[1],  thirdVel[0] - firstVel[0],          0.0,  thirdPos[1] - firstPos[1],  firstPos[0] - thirdPos[0],          0.0 },
        { secondVel[2] - firstVel[2],          0.0,  firstVel[0] - secondVel[0],  firstPos[2] - secondPos[2],          0.0,  secondPos[0] - firstPos[0] },
        { thirdVel[2] - firstVel[2],          0.0,  firstVel[0] - thirdVel[0],  firstPos[2] - thirdPos[2],          0.0,  thirdPos[0] - firstPos[0] },
        {         0.0,  firstVel[2] - secondVel[2],  secondVel[1] - firstVel[1],          0.0,  secondPos[2] - firstPos[2],  firstPos[1] - secondPos[1] },
        {         0.0,  firstVel[2] - thirdVel[2],  thirdVel[1] - firstVel[1],          0.0,  thirdPos[2] - firstPos[2],  firstPos[1] - thirdPos[1] },
    
    };

    vector<long double> h;
    h.push_back((secondPos[1] * secondVel[0] - secondPos[0] * secondVel[1]) - (firstPos[1] * firstVel[0] - firstPos[0] * firstVel[1]));
    h.push_back((thirdPos[1] * thirdVel[0] - thirdPos[0] * thirdVel[1]) - (firstPos[1] * firstVel[0] - firstPos[0] * firstVel[1]));
    h.push_back((secondPos[0] * secondVel[2] - secondPos[2] * secondVel[0]) - (firstPos[0] * firstVel[2] - firstPos[2] * firstVel[0]));
    h.push_back((thirdPos[0] * thirdVel[2] - thirdPos[2] * thirdVel[0]) - (firstPos[0] * firstVel[2] - firstPos[2] * firstVel[0]));
    h.push_back((secondPos[2] * secondVel[1] - secondPos[1] * secondVel[2]) - (firstPos[2] * firstVel[1] - firstPos[1] * firstVel[2]));
    h.push_back((thirdPos[2] * thirdVel[1] - thirdPos[1] * thirdVel[2]) - (firstPos[2] * firstVel[1] - firstPos[1] * firstVel[2]));

    long double inverseMatrix[rows][columns];

    calculateInverse(matrix, inverseMatrix);
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            cout << inverseMatrix[i][j] << " ";
        }
        cout << endl;
    }
    long double result[6];

    multiplyMatrixVector(inverseMatrix, h, result);
}

int main(int argc, char * argv[]){
    if (argc > 1){
        for (int i = 1; i < argc; i++){
            ifstream f(argv[i]);
            if(!f || !readFiles(f, argv[i])){
                return EXIT_FAILURE;
            }
        }
    } else {
        if(!readFiles(cin, "{stdin}"))
            return EXIT_FAILURE;
    } 
    long double sum = check();
    long double part2 = secondPart();
    return 0;
}