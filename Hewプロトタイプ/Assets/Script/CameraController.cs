using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraController : MonoBehaviour
{
    Transform Player1;
    Transform Player2;
    new Camera camera;
    Transform Camera0;

    // Start is called before the first frame update
    void Start()
    {
        Player1 = GameObject.Find("Player1").transform;
        Player2 = GameObject.Find("Player2").transform;
        // メインカメラを取得
        camera = Camera.main;
        Camera0 = camera.gameObject.transform;
    }

    // Update is called once per frame
    void Update()
    {
        float PositionX = (Player1.position.x + Player2.position.x) / 2;
        float PositionZ = (Player1.position.z + Player2.position.z) / 2;

        float criticalX = Mathf.Abs (Player1.position.x - Player2.position.x) / 2 - 10.0f;
        float criticalZ = Mathf.Abs (Player1.position.z - Player2.position.z) / 2 - 8.0f;

        float PositionY = 27.0f + (criticalX > 0 ? criticalX : 0) * 0.8f
            + (criticalZ > 0 ? criticalZ : 0) * 0.8f;

        if (PositionY > 40.0f)
            PositionY = 40.0f;

        float CameraReviseZ = -8.0f - (PositionY - 27.0f) * 0.8f;

        Vector3 CameraPosition = new Vector3(PositionX, PositionY, PositionZ + CameraReviseZ);

        Camera0.position = Vector3.MoveTowards (Camera0.position, CameraPosition, 16.8f * Time.deltaTime) ;
    }
}
