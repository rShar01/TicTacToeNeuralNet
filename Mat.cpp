//
// Created by Ryan on 5/5/2021.
//

#include "Mat.h"

vector<double> Mat::multiply(vector<double> mat_1, vector<double> mat_2) {
    vector<double> ret;
    for(int i = 0; i < mat_1.size(); i++)
        ret.push_back(mat_1[i]*mat_2[i]);

    return ret;
}

vector<double> Mat::add(vector<double> mat_1, vector<double> mat_2) {
    vector<double> ret;
    for(int i = 0; i < mat_1.size(); i++)
        ret.push_back(mat_1[i] + mat_2[i]);

    return ret;
}

double Mat::sum(vector<double> mat) {
    double ret = 0;
    for(auto val:mat)
        ret+=val;

    return 0;
}
