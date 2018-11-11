#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

enum ProgLang
{
    e_cpp,
    e_java,
    e_csharp
};

int conver_main(int argc, char const *argv[])
{
    ProgLang e_test = static_cast<ProgLang>(1);
    std::cout << "over!" << std::endl;
    return 0;
}

// 一维滤波器信息结构体
typedef  struct 
{
    float filterValue;  //k-1时刻的滤波值，即是k-1时刻的值
    float kalmanGain;   //   Kalamn增益
    float A;   // x(n)=A*x(n-1)+u(n),u(n)~N(0,Q)
    float H;   // z(n)=H*x(n)+w(n),w(n)~N(0,R)
    float Q;   //预测过程噪声偏差的方差
    float R;   //测量噪声偏差，(系统搭建好以后，通过测量统计实验获得)
    float P;   //估计误差协方差
}  KalmanInfo;
/**
* @brief Init_KalmanInfo   初始化滤波器的初始值
* @param info  滤波器指针
* @param Q 预测噪声方差 由系统外部测定给定
* @param R 测量噪声方差 由系统外部测定给定
*/
void Init_KalmanInfo(KalmanInfo* info, float Q, float R)
{
    info->A = 1;  //标量卡尔曼
    info->H = 1;  //
    info->P = 980;  //后验状态估计值误差的方差的初始值
    info->Q = Q;    //预测（过程）噪声方差 影响收敛速率，可以根据实际需求给出
    info->R = R;    //测量（观测）噪声方差 可以通过实验手段获得
    info->filterValue = 0;// 测量的初始值
}
float KalmanFilter(KalmanInfo* kalmanInfo, float lastMeasurement)
{
    //预测下一时刻的值
    float predictValue = kalmanInfo->A* kalmanInfo->filterValue;  

    kalmanInfo->P = kalmanInfo->A*kalmanInfo->A*kalmanInfo->P + kalmanInfo->Q;  //计算先验均方差 p(n|n-1)=A^2*p(n-1|n-1)+q
    float preValue = kalmanInfo->filterValue;  //记录上次实际坐标的值

    //计算kalman增益
    kalmanInfo->kalmanGain = kalmanInfo->P*kalmanInfo->H / (kalmanInfo->P*kalmanInfo->H*kalmanInfo->H + kalmanInfo->R);  //Kg(k)= P(k|k-1) H’ / (H P(k|k-1) H’ + R)
    //修正结果，即计算滤波值
    kalmanInfo->filterValue = predictValue + (lastMeasurement - predictValue)*kalmanInfo->kalmanGain;  //利用残余的信息改善对x(t)的估计，给出后验估计，X(k|k)= X(k|k-1)+Kg(k) (Z(k)-H X(k|k-1))
     //更新后验估计
    kalmanInfo->P = (1 - kalmanInfo->kalmanGain*kalmanInfo->H)*kalmanInfo->P; //计算后验均方差  P[n|n]=(1-K[n]*H)*P[n|n-1]

    printf("%.3f \n", kalmanInfo->filterValue);
    return  kalmanInfo->filterValue;
}

int main() 
{
    KalmanInfo myKalm;
    Init_KalmanInfo(&myKalm,2, 80);
    KalmanFilter(&myKalm, 968.125);
    KalmanFilter(&myKalm, 994.844);
    KalmanFilter(&myKalm, 1005.938);
    KalmanFilter(&myKalm, 1040.469);
    KalmanFilter(&myKalm, 1082.813);
    KalmanFilter(&myKalm, 1054.844);
    KalmanFilter(&myKalm, 1050.313);
    KalmanFilter(&myKalm, 1092.656);
    KalmanFilter(&myKalm, 1162.344);
    KalmanFilter(&myKalm, 1142.188);
    KalmanFilter(&myKalm, 1133.75);
    KalmanFilter(&myKalm, 1129.219);
    KalmanFilter(&myKalm, 1218.438);
    KalmanFilter(&myKalm, 1210);
    KalmanFilter(&myKalm, 1217.188);
    KalmanFilter(&myKalm, 1212.656);
    KalmanFilter(&myKalm, 1176.875);
    KalmanFilter(&myKalm, 270.00 );
    KalmanFilter(&myKalm, 1363.125);
    KalmanFilter(&myKalm, 1253.125);
    KalmanFilter(&myKalm, 1346.25);
    KalmanFilter(&myKalm, 1314.375);
    KalmanFilter(&myKalm, 1169.219);
    KalmanFilter(&myKalm, 1188.125);
    KalmanFilter(&myKalm, 1226.563);
    KalmanFilter(&myKalm, 1382.188);
    KalmanFilter(&myKalm, 619.844);
    KalmanFilter(&myKalm, 1466.875);
    KalmanFilter(&myKalm, 1392.031);
    KalmanFilter(&myKalm, 1555.469);
    KalmanFilter(&myKalm, 1699.375);
    KalmanFilter(&myKalm, 1702.656);
    KalmanFilter(&myKalm, 1592.656);
    KalmanFilter(&myKalm, 1365.469);
    KalmanFilter(&myKalm, 1317.969);
    KalmanFilter(&myKalm, 1407.188);
    KalmanFilter(&myKalm, 1570.625);
    KalmanFilter(&myKalm, 1687.188);
    KalmanFilter(&myKalm, 1741.25);
    KalmanFilter(&myKalm, 1732.813);
    KalmanFilter(&myKalm, 1779.063);
    KalmanFilter(&myKalm, 1833.125);
    KalmanFilter(&myKalm, 1367.656);
    KalmanFilter(&myKalm, 1410);
    KalmanFilter(&myKalm, 1483.594);
    KalmanFilter(&myKalm, 1604.063);
    KalmanFilter(&myKalm, 1790.938);
    KalmanFilter(&myKalm, 1704.375);
    KalmanFilter(&myKalm, 1707.656);
    KalmanFilter(&myKalm, 1742.188);
    KalmanFilter(&myKalm, 1854.844);
    KalmanFilter(&myKalm, 2155);
    KalmanFilter(&myKalm, 2111.406);
    KalmanFilter(&myKalm, 966.25);
    KalmanFilter(&myKalm, 1789.844);
    KalmanFilter(&myKalm, 1398.594);
    KalmanFilter(&myKalm, 1452.656);
    KalmanFilter(&myKalm, 1709.844);
    KalmanFilter(&myKalm, 916.25);
    KalmanFilter(&myKalm, 2161.719);
    KalmanFilter(&myKalm, 2247.031);
    KalmanFilter(&myKalm, 2019.844);
    KalmanFilter(&myKalm, 1968.438);
    KalmanFilter(&myKalm, 1838.906);
    KalmanFilter(&myKalm, 1932.031);
    KalmanFilter(&myKalm, 1751.719);
    KalmanFilter(&myKalm, 1680.781);
    KalmanFilter(&myKalm, 2102.031);
    KalmanFilter(&myKalm, 2210.781);
    KalmanFilter(&myKalm, 2327.344);
    KalmanFilter(&myKalm, 2088.438);
    KalmanFilter(&myKalm, 2326.094);
    KalmanFilter(&myKalm, 2372.344);
    KalmanFilter(&myKalm, 2027.969);
    KalmanFilter(&myKalm, 1964.844);
    KalmanFilter(&myKalm, 1948.594);
    KalmanFilter(&myKalm, 2026.094);
    KalmanFilter(&myKalm, 1998.125);
    KalmanFilter(&myKalm, 1985.781);
    KalmanFilter(&myKalm, 2285.938);





    return 0;
}
