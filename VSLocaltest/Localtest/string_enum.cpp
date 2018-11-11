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

// һά�˲�����Ϣ�ṹ��
typedef  struct 
{
    float filterValue;  //k-1ʱ�̵��˲�ֵ������k-1ʱ�̵�ֵ
    float kalmanGain;   //   Kalamn����
    float A;   // x(n)=A*x(n-1)+u(n),u(n)~N(0,Q)
    float H;   // z(n)=H*x(n)+w(n),w(n)~N(0,R)
    float Q;   //Ԥ���������ƫ��ķ���
    float R;   //��������ƫ�(ϵͳ����Ժ�ͨ������ͳ��ʵ����)
    float P;   //�������Э����
}  KalmanInfo;
/**
* @brief Init_KalmanInfo   ��ʼ���˲����ĳ�ʼֵ
* @param info  �˲���ָ��
* @param Q Ԥ���������� ��ϵͳ�ⲿ�ⶨ����
* @param R ������������ ��ϵͳ�ⲿ�ⶨ����
*/
void Init_KalmanInfo(KalmanInfo* info, float Q, float R)
{
    info->A = 1;  //����������
    info->H = 1;  //
    info->P = 980;  //����״̬����ֵ���ķ���ĳ�ʼֵ
    info->Q = Q;    //Ԥ�⣨���̣��������� Ӱ���������ʣ����Ը���ʵ���������
    info->R = R;    //�������۲⣩�������� ����ͨ��ʵ���ֶλ��
    info->filterValue = 0;// �����ĳ�ʼֵ
}
float KalmanFilter(KalmanInfo* kalmanInfo, float lastMeasurement)
{
    //Ԥ����һʱ�̵�ֵ
    float predictValue = kalmanInfo->A* kalmanInfo->filterValue;  

    kalmanInfo->P = kalmanInfo->A*kalmanInfo->A*kalmanInfo->P + kalmanInfo->Q;  //������������� p(n|n-1)=A^2*p(n-1|n-1)+q
    float preValue = kalmanInfo->filterValue;  //��¼�ϴ�ʵ�������ֵ

    //����kalman����
    kalmanInfo->kalmanGain = kalmanInfo->P*kalmanInfo->H / (kalmanInfo->P*kalmanInfo->H*kalmanInfo->H + kalmanInfo->R);  //Kg(k)= P(k|k-1) H�� / (H P(k|k-1) H�� + R)
    //����������������˲�ֵ
    kalmanInfo->filterValue = predictValue + (lastMeasurement - predictValue)*kalmanInfo->kalmanGain;  //���ò������Ϣ���ƶ�x(t)�Ĺ��ƣ�����������ƣ�X(k|k)= X(k|k-1)+Kg(k) (Z(k)-H X(k|k-1))
     //���º������
    kalmanInfo->P = (1 - kalmanInfo->kalmanGain*kalmanInfo->H)*kalmanInfo->P; //������������  P[n|n]=(1-K[n]*H)*P[n|n-1]

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
