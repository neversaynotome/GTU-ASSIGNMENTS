using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.XR.ARFoundation;
using UnityEngine.XR.ARSubsystems;

[RequireComponent(typeof(ARTrackedImageManager))]
public class Tracker : MonoBehaviour
{
    private ARTrackedImageManager _trackedImageManager;
    public GameObject[] AR_prefabs;
    private readonly Dictionary<string, GameObject> _instantiatedPrefabs = new Dictionary<string, GameObject>();
    private void Awake()
    {
        _trackedImageManager = GetComponent<ARTrackedImageManager>();
    }
        void OnEnable()
    {
        _trackedImageManager.trackedImagesChanged += TrackedImage;
    }
    private void OnDisable()
    {
        _trackedImageManager.trackedImagesChanged -= TrackedImage;
    }
    private void TrackedImage(ARTrackedImagesChangedEventArgs eventArgs)
    {
        foreach (var trackedImage in eventArgs.added)
        {
            var imageName = trackedImage.referenceImage.name;

            foreach (var prefab in AR_prefabs)
            {
                if(string.Compare(prefab.name, imageName, StringComparison.OrdinalIgnoreCase) == 0 && !_instantiatedPrefabs.ContainsKey(imageName))
                {
                    var newPrefab = Instantiate(prefab, trackedImage.transform);
                    newPrefab.SetActive(true);

                    _instantiatedPrefabs[imageName] = newPrefab;
                }
            }

        }
        foreach (var trackedImage in eventArgs.updated)
        {
            _instantiatedPrefabs[trackedImage.referenceImage.name].SetActive(trackedImage.trackingState == TrackingState.Tracking);     
        }

        foreach(var trackedImage in eventArgs.removed)
        {
            Destroy(_instantiatedPrefabs[trackedImage.referenceImage.name]);
            _instantiatedPrefabs.Remove(trackedImage.referenceImage.name);  
        }
    }
}
