using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Accord.Math; 
using Accord.Math.Decompositions;
using Accord.Imaging;
using Accord.Math.Geometry;


public class PointAligner : MonoBehaviour
{
    public bool globalScale = false;
    public float scaleX = 1;
    public float scaleY = 1;
    public float scaleZ = 1;
    public float alignmentPrecision = 0.2f;
    public GameObject Ppoints;
    public GameObject Qpoints;
    public bool showTransformation = true;
    public bool drawLines = true;
    public int iteration = 1000;
    public bool unlimitedCalculation = false;
    public bool calculate = false;
    public float debug;

    private bool isAligned = false;
    private bool isRead = false;
    private List<Accord.Math.Vector3> pointsP;
    private List<Accord.Math.Vector3> pointsQ;

    void Update()
    {  
        if (!isRead && calculate)
        {
            pointsP = new List<Accord.Math.Vector3>();
            pointsQ = new List<Accord.Math.Vector3>();

            for(int i = 0; i < Qpoints.transform.childCount; i++)
            {
                pointsP.Add(new Accord.Math.Vector3(Qpoints.transform.GetChild(i).position.x, Qpoints.transform.GetChild(i).position.y, Qpoints.transform.GetChild(i).position.z));
            }

            for(int i = 0; i < Ppoints.transform.childCount; i++)
            {
                pointsQ.Add(new Accord.Math.Vector3(Ppoints.transform.GetChild(i).position.x, Ppoints.transform.GetChild(i).position.y, Ppoints.transform.GetChild(i).position.z));
            }
            isRead = true;
        }

        if(!isAligned && calculate){
            Align();
        }
    }

    // Here is where alingment is done by RANSAC algorithm
    void Align(){
        // these vectors and matrices will hold best ransformations
        Accord.Math.Vector3 translation;
        Accord.Math.Matrix3x3 rotation;
        float scale;
        GetBestTransformation(pointsP, pointsQ, out translation, out rotation, out scale);

        // Now transformation will be done

        for(int i = 0; i < Ppoints.transform.childCount; i++)
        {
            Accord.Math.Vector3 point = new Accord.Math.Vector3(Ppoints.transform.GetChild(i).position.x, Ppoints.transform.GetChild(i).position.y, Ppoints.transform.GetChild(i).position.z);
            // If global scale is marked true by user 
            if (globalScale)
            {
                Accord.Math.Matrix3x3 scaleMatrix = new Accord.Math.Matrix3x3();
                scaleMatrix.V00 = scaleX;
                scaleMatrix.V01 = 0;
                scaleMatrix.V02 = 0;
                scaleMatrix.V10 = 0;
                scaleMatrix.V11 = scaleY;
                scaleMatrix.V12 = 0;
                scaleMatrix.V20 = 0;
                scaleMatrix.V21 = 0;
                scaleMatrix.V22 = scaleZ;
                point = rotation * point;
                point = scaleMatrix * point;
                point = point + translation;
            }else
            {   
                point = rotation * point;
                point = point + translation;
            }
            
            if(drawLines){

                Ppoints.transform.GetChild(i).gameObject.AddComponent<LineRenderer>();
                LineRenderer lr2 = Ppoints.transform.GetChild(i).GetComponent<LineRenderer>();
                lr2.material = new Material(Shader.Find("Sprites/Default"));
                lr2.startColor = Color.white;
                lr2.endColor = Color.white;
                lr2.startWidth = 0.1f;
                lr2.endWidth = 0.1f;
                lr2.SetPosition(0, Ppoints.transform.GetChild(i).position);
                lr2.SetPosition(1, new UnityEngine.Vector3(point.X, point.Y, point.Z));
            }         

            if (showTransformation){
                Ppoints.transform.GetChild(i).position = new UnityEngine.Vector3(point.X, point.Y, point.Z);
            }

        }
        //debug = scale;
        isAligned = true;
        Debug.Log("Aligned");
    }

    // RANSAC method gives the best position of aligned points
    void GetBestTransformation(List<Accord.Math.Vector3> pointsP, List<Accord.Math.Vector3> pointsQ, out Accord.Math.Vector3 translation, out Accord.Math.Matrix3x3 rotation, out float scale){
        
        int bestInliers = 0;
        Accord.Math.Vector3 bestTranslation = new Accord.Math.Vector3();
        bestTranslation.X = 0;
        bestTranslation.Y = 0;
        bestTranslation.Z = 0;

        Accord.Math.Matrix3x3 bestRotation = new Accord.Math.Matrix3x3();
        bestRotation.V00 = 1;
        bestRotation.V01 = 0;
        bestRotation.V02 = 0;
        bestRotation.V10 = 0;
        bestRotation.V11 = 1;
        bestRotation.V12 = 0;
        bestRotation.V20 = 0;
        bestRotation.V21 = 0;
        bestRotation.V22 = 1;

        float bestScale = 1;

        for(int i = 0; i < iteration || unlimitedCalculation ; i++){

            Debug.Log("Iteration");

            int index_1_1 = Random.Range(0, pointsP.Count);
            int index_1_2 = Random.Range(0, pointsP.Count);
            int index_1_3 = Random.Range(0, pointsP.Count);

            int index_2_1 = Random.Range(0, pointsQ.Count);
            int index_2_2 = Random.Range(0, pointsQ.Count);
            int index_2_3 = Random.Range(0, pointsQ.Count);

            Accord.Math.Vector3 point_1_1 = pointsP[index_1_1];
            Accord.Math.Vector3 point_1_2 = pointsP[index_1_2];
            Accord.Math.Vector3 point_1_3 = pointsP[index_1_3];

            Accord.Math.Vector3 point_2_1 = pointsQ[index_2_1];
            Accord.Math.Vector3 point_2_2 = pointsQ[index_2_2];
            Accord.Math.Vector3 point_2_3 = pointsQ[index_2_3];

            Accord.Math.Vector3 translation_temp;
            Accord.Math.Matrix3x3 rotation_temp;
            float scale_temp;

            GetTransformation(point_1_1, point_1_2, point_1_3, point_2_1, point_2_2, point_2_3, out translation_temp, out rotation_temp, out scale_temp);

            Accord.Math.Matrix3x3 scaleMatrix = new Accord.Math.Matrix3x3();
            scaleMatrix.V00 = scale_temp;
            scaleMatrix.V01 = 0;
            scaleMatrix.V02 = 0;
            scaleMatrix.V10 = 0;
            scaleMatrix.V11 = scale_temp;
            scaleMatrix.V12 = 0;
            scaleMatrix.V20 = 0;
            scaleMatrix.V21 = 0;
            scaleMatrix.V22 = scale_temp;

            List<Accord.Math.Vector3> points_2_temp = new List<Accord.Math.Vector3>();
            for(int j = 0; j < pointsQ.Count; j++)
            {
                Accord.Math.Vector3 point_temp = rotation_temp * pointsQ[j] + translation_temp;
                points_2_temp.Add(point_temp);
            }

            int inliers = 0;
            for(int j = 0; j < pointsP.Count; j++)
            {   
                inliers = CountOverlappingPoints(pointsP, points_2_temp, alignmentPrecision);
            }

            // if inliers are more than the previous bestInliers than we have a better match
            if(inliers > bestInliers){
                bestInliers = inliers;
                bestTranslation = translation_temp;
                bestRotation = rotation_temp;
                bestScale = scale_temp;
            }

            if(bestInliers > pointsP.Count / 2) break;
        }

        Debug.Log("Best inliers: " + bestInliers);
        translation = bestTranslation;
        rotation = bestRotation;
        scale = bestScale;
    }


    void GetTransformation(Accord.Math.Vector3 point_1_1, Accord.Math.Vector3 point_1_2, Accord.Math.Vector3 point_1_3, Accord.Math.Vector3 point_2_1, Accord.Math.Vector3 point_2_2, Accord.Math.Vector3 point_2_3, out Accord.Math.Vector3 translation, out Accord.Math.Matrix3x3 rotation, out float scale){

        Accord.Math.Vector3 centroid_1 = new Accord.Math.Vector3();
        centroid_1.X = (point_1_1.X + point_1_2.X + point_1_3.X) / 3;
        centroid_1.Y = (point_1_1.Y + point_1_2.Y + point_1_3.Y) / 3;
        centroid_1.Z = (point_1_1.Z + point_1_2.Z + point_1_3.Z) / 3;

        Accord.Math.Vector3 centroid_2 = new Accord.Math.Vector3();
        centroid_2.X = (point_2_1.X + point_2_2.X + point_2_3.X) / 3;
        centroid_2.Y = (point_2_1.Y + point_2_2.Y + point_2_3.Y) / 3;
        centroid_2.Z = (point_2_1.Z + point_2_2.Z + point_2_3.Z) / 3;

        Accord.Math.Vector3 point_1_1_relative = new Accord.Math.Vector3();
        point_1_1_relative.X = point_1_1.X - centroid_1.X;
        point_1_1_relative.Y = point_1_1.Y - centroid_1.Y;
        point_1_1_relative.Z = point_1_1.Z - centroid_1.Z;

        Accord.Math.Vector3 point_1_2_relative = new Accord.Math.Vector3();
        point_1_2_relative.X = point_1_2.X - centroid_1.X;
        point_1_2_relative.Y = point_1_2.Y - centroid_1.Y;
        point_1_2_relative.Z = point_1_2.Z - centroid_1.Z;

        Accord.Math.Vector3 point_1_3_relative = new Accord.Math.Vector3();
        point_1_3_relative.X = point_1_3.X - centroid_1.X;
        point_1_3_relative.Y = point_1_3.Y - centroid_1.Y;
        point_1_3_relative.Z = point_1_3.Z - centroid_1.Z;

        Accord.Math.Vector3 point_2_1_relative = new Accord.Math.Vector3();
        point_2_1_relative.X = point_2_1.X - centroid_2.X;
        point_2_1_relative.Y = point_2_1.Y - centroid_2.Y;
        point_2_1_relative.Z = point_2_1.Z - centroid_2.Z;

        Accord.Math.Vector3 point_2_2_relative = new Accord.Math.Vector3();
        point_2_2_relative.X = point_2_2.X - centroid_2.X;
        point_2_2_relative.Y = point_2_2.Y - centroid_2.Y;
        point_2_2_relative.Z = point_2_2.Z - centroid_2.Z;

        Accord.Math.Vector3 point_2_3_relative = new Accord.Math.Vector3();
        point_2_3_relative.X = point_2_3.X - centroid_2.X;
        point_2_3_relative.Y = point_2_3.Y - centroid_2.Y;
        point_2_3_relative.Z = point_2_3.Z - centroid_2.Z;

        Accord.Math.Matrix3x3 matrix_1 = new Accord.Math.Matrix3x3();
        matrix_1.V00 = point_1_1_relative.X;
        matrix_1.V01 = point_1_1_relative.Y;
        matrix_1.V02 = point_1_1_relative.Z;
        matrix_1.V10 = point_1_2_relative.X;
        matrix_1.V11 = point_1_2_relative.Y;
        matrix_1.V12 = point_1_2_relative.Z;
        matrix_1.V20 = point_1_3_relative.X;
        matrix_1.V21 = point_1_3_relative.Y;
        matrix_1.V22 = point_1_3_relative.Z;

        Accord.Math.Matrix3x3 matrix_2 = new Accord.Math.Matrix3x3();
        matrix_2.V00 = point_2_1_relative.X;
        matrix_2.V01 = point_2_1_relative.Y;
        matrix_2.V02 = point_2_1_relative.Z;
        matrix_2.V10 = point_2_2_relative.X;
        matrix_2.V11 = point_2_2_relative.Y;
        matrix_2.V12 = point_2_2_relative.Z;
        matrix_2.V20 = point_2_3_relative.X;
        matrix_2.V21 = point_2_3_relative.Y;
        matrix_2.V22 = point_2_3_relative.Z;

        Accord.Math.Matrix3x3 H = new Accord.Math.Matrix3x3();
        H = matrix_1 * matrix_2.Transpose();

        H.SVD(out Accord.Math.Matrix3x3 U, out Accord.Math.Vector3 S, out Accord.Math.Matrix3x3 V);

        Accord.Math.Matrix3x3 R = new Accord.Math.Matrix3x3();
        R = V * U.Transpose();

        if(Determinant(R) < 0){
            R.SVD(out Accord.Math.Matrix3x3 U_temp, out Accord.Math.Vector3 S_temp, out Accord.Math.Matrix3x3 V_temp);
            V_temp.V20 = -V_temp.V00;
            V_temp.V21 = -V_temp.V01;
            V_temp.V22 = -V_temp.V02;
            R = V_temp * U_temp.Transpose();
        }

        float scale_temp = (S.X + S.Y + S.Z) / 3f;
        translation = centroid_2 - R * centroid_1;
        rotation = R;
        scale = scale_temp;
    }

    // If points are within the threshold then it is accepted as a match
    int CountOverlappingPoints(List<Accord.Math.Vector3> pointsP, List<Accord.Math.Vector3> pointsQ, float alignmentPrecision)
    {
        int overlappingPoints = 0;
        int[] overlappingPoints_1 = new int[pointsP.Count]; 

        for(int i = 0; i < pointsP.Count; i++)
        {
            for(int j = 0; j < pointsQ.Count; j++)
            {
                if(DistanceTwoAccordVector(pointsP[i], pointsQ[j]) < alignmentPrecision && overlappingPoints_1[i] == 0)
                {
                    overlappingPoints++;
                    overlappingPoints_1[i] = 1;
                    break;
                }
            }
        }

        return overlappingPoints;
    }


    public float DistanceTwoAccordVector(Accord.Math.Vector3 point_1, Accord.Math.Vector3 point_2){
        return (float)Mathf.Sqrt(Mathf.Pow(point_1.X - point_2.X, 2) + Mathf.Pow(point_1.Y - point_2.Y, 2) + Mathf.Pow(point_1.Z - point_2.Z, 2));
    }

    public Accord.Math.Vector3 Convert(UnityEngine.Vector3 v){

        Accord.Math.Vector3 v_temp = new Accord.Math.Vector3();
        v_temp.X = v.x;
        v_temp.Y = v.y;
        v_temp.Z = v.z;

        return v_temp;
    }

    public UnityEngine.Vector3 Convert(Accord.Math.Vector3 v){
        return new UnityEngine.Vector3((float)v.X, (float)v.Y, (float)v.Z);
    }

    public Accord.Math.Matrix3x3 Convert(UnityEngine.Quaternion q){
        
        Accord.Math.Matrix3x3 m = new Accord.Math.Matrix3x3();
        m.V00 = 1 - 2 * q.y * q.y - 2 * q.z * q.z;
        m.V01 = 2 * q.x * q.y - 2 * q.z * q.w;
        m.V02 = 2 * q.x * q.z + 2 * q.y * q.w;
        m.V10 = 2 * q.x * q.y + 2 * q.z * q.w;
        m.V11 = 1 - 2 * q.x * q.x - 2 * q.z * q.z;
        m.V12 = 2 * q.y * q.z - 2 * q.x * q.w;
        m.V20 = 2 * q.x * q.z - 2 * q.y * q.w;
        m.V21 = 2 * q.y * q.z + 2 * q.x * q.w;
        m.V22 = 1 - 2 * q.x * q.x - 2 * q.y * q.y;

        return m;
    }

    public UnityEngine.Quaternion Convert(Accord.Math.Matrix3x3 m){

        UnityEngine.Quaternion q = new UnityEngine.Quaternion();
        q.w = Mathf.Sqrt(Mathf.Max(0, 1 + m.V00 + m.V11 + m.V22)) / 2;
        q.x = Mathf.Sqrt(Mathf.Max(0, 1 + m.V00 - m.V11 - m.V22)) / 2;
        q.y = Mathf.Sqrt(Mathf.Max(0, 1 - m.V00 + m.V11 - m.V22)) / 2;
        q.z = Mathf.Sqrt(Mathf.Max(0, 1 - m.V00 - m.V11 + m.V22)) / 2;
        q.x *= Mathf.Sign(q.x * (m.V21 - m.V12));
        q.y *= Mathf.Sign(q.y * (m.V02 - m.V20));
        q.z *= Mathf.Sign(q.z * (m.V10 - m.V01));

        return q;
    }

    public float Determinant(Accord.Math.Matrix3x3 m){
        return m.V00 * (m.V11 * m.V22 - m.V12 * m.V21) - m.V01 * (m.V10 * m.V22 - m.V12 * m.V20) + m.V02 * (m.V10 * m.V21 - m.V11 * m.V20);
    }
    
    Accord.Math.Matrix3x3 Multiply(double[,] A, double[,] B){

        Accord.Math.Matrix3x3 C = new Accord.Math.Matrix3x3();
        float[,] C_array = new float[3,3];

        for(int i=0; i<3; ++i){
            for(int j=0; j<3; ++j){
                for(int k=0; k<3; ++k){
                    C_array[i,j] += (float)(A[i,k] * B[k,j]);
                }
            }
        }

        C.V00 = C_array[0,0];
        C.V01 = C_array[0,1];
        C.V02 = C_array[0,2];
        C.V10 = C_array[1,0];
        C.V11 = C_array[1,1];
        C.V12 = C_array[1,2];
        C.V20 = C_array[2,0];
        C.V21 = C_array[2,1];
        C.V22 = C_array[2,2];

        return C;
    }

    Accord.Math.Matrix3x3 Multiply(Accord.Math.Matrix3x3 A, Accord.Math.Matrix3x3 B)
    {
        Accord.Math.Matrix3x3 C = new Accord.Math.Matrix3x3();
        float[,] C_array = new float[3,3];
        float[,] A_array = new float[3,3];
        float[,] B_array = new float[3,3];

        for(int i=0; i<3; ++i){
            A_array[i,0] = A.GetRow(0).X;
            A_array[i,1] = A.GetRow(0).Y;
            A_array[i,2] = A.GetRow(0).Z;
            B_array[i,0] = B.GetRow(0).X;
            B_array[i,1] = B.GetRow(0).Y;
            B_array[i,2] = B.GetRow(0).Z;
        }

        for(int i=0; i<3; ++i){
            for(int j=0; j<3; ++j){
                C_array[i,j] = 0;
                for(int k=0; k<3; ++k){
                    C_array[i,j] += A_array[i,k] * B_array[k,j];
                }
            }
        }

        C.V00 = C_array[0,0];
        C.V01 = C_array[0,1];
        C.V02 = C_array[0,2];
        C.V10 = C_array[1,0];
        C.V11 = C_array[1,1];
        C.V12 = C_array[1,2];
        C.V20 = C_array[2,0];
        C.V21 = C_array[2,1];
        C.V22 = C_array[2,2];

        return C;
    }

    UnityEngine.Vector3 Multiply(Accord.Math.Matrix3x3 A, UnityEngine.Vector3 B)
    {
        float[,] A_array = new float[3,3];
        float[] B_array = new float[3];

        for(int i=0; i<3; ++i){
            A_array[i,0] = A.GetRow(0).X;
            A_array[i,1] = A.GetRow(0).Y;
            A_array[i,2] = A.GetRow(0).Z;
        }

        B_array[0] = B.x;
        B_array[1] = B.y;
        B_array[2] = B.z;

        UnityEngine.Vector3 C = new UnityEngine.Vector3();

        for(int i=0; i<3; ++i){
            C[i] = 0;
            for(int j=0; j<3; ++j){
                C[i] += A_array[i,j] * B_array[j];
            }
        }
        return C;
    }

    Accord.Math.Vector3 Multiply(double[,] A, Accord.Math.Vector3 B)
    {
        float[,] A_array = new float[3,3];
        float[] B_array = new float[3];

        for(int i=0; i<3; ++i){
            A_array[i,0] = (float)A[i,0];
            A_array[i,1] = (float)A[i,1];
            A_array[i,2] = (float)A[i,2];
        }

        B_array[0] = B.X;
        B_array[1] = B.Y;
        B_array[2] = B.Z;

        Accord.Math.Vector3 C = new Accord.Math.Vector3();
        float[] C_array = new float[3];

        for(int i=0; i<3; ++i){
            C_array[i] = 0;
            for(int j=0; j<3; ++j){
                C_array[i] += A_array[i,j] * B_array[j];
            }
        }

        C.X = C_array[0];
        C.Y = C_array[1];
        C.Z = C_array[2];

        return C;
    }

    Accord.Math.Matrix3x3 Transpose(Accord.Math.Matrix3x3 A)
    {
        Accord.Math.Matrix3x3 B = new Accord.Math.Matrix3x3();
        float[,] B_array = new float[3,3];

        for(int i=0; i<3; ++i){
            B_array[i,0] = A.GetRow(0).X;
            B_array[i,1] = A.GetRow(0).Y;
            B_array[i,2] = A.GetRow(0).Z;
        }

        B.V00 = B_array[0,0];
        B.V01 = B_array[1,0];
        B.V02 = B_array[2,0];
        B.V10 = B_array[0,1];
        B.V11 = B_array[1,1];
        B.V12 = B_array[2,1];
        B.V20 = B_array[0,2];
        B.V21 = B_array[1,2];
        B.V22 = B_array[2,2];

        return B;
    }

}