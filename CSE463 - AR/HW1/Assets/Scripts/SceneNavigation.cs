using UnityEngine;

public class GameObjectController : MonoBehaviour
{
    public GameObject[] objectsToToggle;
    private int currentIndex = 0;

    // Start is called before the first frame update
    void Start()
    {
        // Initialize the visibility of game objects
        UpdateVisibility();
    }

    // Update is called once per frame
    void Update()
    {
        // You can add additional logic here if needed
    }

    // Function to toggle the visibility of game objects
    void UpdateVisibility()
    {
        // Hide all game objects
        foreach (GameObject obj in objectsToToggle)
        {
            obj.SetActive(false);
        }

        // Show the current game object
        objectsToToggle[currentIndex].SetActive(true);
    }

    // Function to handle the button click
    public void OnButtonClick()
    {
        // Toggle to the next game object
        currentIndex = (currentIndex + 1) % objectsToToggle.Length;

        // Update the visibility
        UpdateVisibility();
    }
}
