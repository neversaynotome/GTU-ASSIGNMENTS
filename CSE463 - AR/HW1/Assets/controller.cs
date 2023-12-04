using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class controller : MonoBehaviour
{
    [SerializeField] private float speed;

    private FixedJoystick fJoystick;
    private Rigidbody rb;

    private void OnEnable()
    {
        fJoystick = FindObjectOfType<FixedJoystick>();
        rb = gameObject.GetComponent<Rigidbody>();
    }

    private void FixedUpdate()
    {
        float xVal = fJoystick.Horizontal;
        float yVal = fJoystick.Vertical;

        Vector3 movement = new Vector3(xVal, 0, yVal);
        rb.velocity =   movement * speed;

        if(xVal != 0 && yVal != 0)
        {
            transform.eulerAngles = new Vector3(transform.eulerAngles.x, Mathf.Atan2(xVal, yVal)*Mathf.Rad2Deg, transform.eulerAngles.z);
        }
    }
}
