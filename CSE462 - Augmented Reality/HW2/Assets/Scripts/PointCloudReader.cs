using UnityEngine;
using System.Collections.Generic;
using System.IO;

public class PointLoader : MonoBehaviour
{
    public string file1Path;
    public string file2Path;
    public GameObject spherePrefab; // Reference to the sphere prefab
    public Material materialForP;
    public Material materialForQ;

    void Awake()
    {
        CreateParentObject("Ppoints");
        LoadAndCreatePoints(file1Path, materialForP, "Ppoints");

        CreateParentObject("Qpoints");
        LoadAndCreatePoints(file2Path, materialForQ, "Qpoints");
    }

    void CreateParentObject(string parentName)
    {
        GameObject parentObject = new GameObject(parentName);
        parentObject.transform.parent = transform;
    }

    void LoadAndCreatePoints(string filePath, Material material, string parentName)
    {
        List<Vector3> points = ReadPointsFromFile(filePath);

        if (points != null)
        {
            GameObject parentObject = transform.Find(parentName).gameObject;

            foreach (Vector3 point in points)
            {
                GameObject sphere = Instantiate(spherePrefab, point, Quaternion.identity);
                sphere.GetComponent<Renderer>().material = material;
                sphere.transform.parent = parentObject.transform;
            }
        }
    }

    List<Vector3> ReadPointsFromFile(string filePath)
    {
        List<Vector3> points = new List<Vector3>();

        try
        {
            string[] lines = File.ReadAllLines(filePath);

            foreach (string line in lines)
            {
                string[] coordinates = line.Split(' ');

                if (coordinates.Length == 3)
                {
                    float x = float.Parse(coordinates[0]);
                    float y = float.Parse(coordinates[1]);
                    float z = float.Parse(coordinates[2]);

                    points.Add(new Vector3(x, y, z));
                }
            }
        }
        catch (FileNotFoundException)
        {
            Debug.LogError($"File not found: {filePath}");
            return null;
        }
        catch (System.Exception e)
        {
            Debug.LogError($"Error reading file {filePath}: {e.Message}");
            return null;
        }

        return points;
    }
}
