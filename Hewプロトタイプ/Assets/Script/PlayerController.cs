using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    Transform Player1;
    Transform Player2;
    float g_AngleP1;
    float g_AngleP2;

    // Start is called before the first frame update
    void Start()
    {
        Player1 = GameObject.Find("Player1").transform;
        Player2 = GameObject.Find("Player2").transform;
        g_AngleP1 = 0.0f;
        g_AngleP2 = 0.0f;
    }

    // Update is called once per frame
    void Update()
    {

        int angleFlagP1 = 0;
        int angleFlagP2 = 0; 

        //プレイヤー1
        if (Input.GetKey("w"))
        {
            angleFlagP1 += 1;
            Player1.position += transform.forward * ((Input.GetKey("a") || Input.GetKey("d")) ? 12 : 17) * Time.deltaTime;
        }

        if (Input.GetKey("s"))
        {
            angleFlagP1 += 5;
            Player1.position -= transform.forward * ((Input.GetKey("a") || Input.GetKey("d")) ? 12 : 17) * Time.deltaTime;
        }

        if (Input.GetKey("a"))
        {
            angleFlagP1 += -7;
            Player1.position -= transform.right * ((Input.GetKey("w") || Input.GetKey("s")) ? 12 : 17) * Time.deltaTime;
        }

        if (Input.GetKey("d"))
        {
            angleFlagP1 += 3;
            Player1.position += transform.right * ((Input.GetKey("w") || Input.GetKey("s")) ? 12 : 17) * Time.deltaTime;
        }

        if (angleFlagP1 != 0)
        {

            switch (angleFlagP1)
            {
                case 1:
                    g_AngleP1 = 0.0f;
                    break;
                case 3:
                    g_AngleP1 = 90.0f;
                    break;
                case 5:
                    g_AngleP1 = 180.0f;
                    break;
                case -7:
                    g_AngleP1 = -90.0f;
                    break;
                case 4:
                    g_AngleP1 = 45.0f;
                    break;
                case 8:
                    g_AngleP1 = 135.0f;
                    break;
                case -2:
                    g_AngleP1 = -135.0f;
                    break;
                case -6:
                    g_AngleP1 = -45.0f;
                    break;
                default:
                    break;
            }

            Player1.rotation = Quaternion.Slerp(Player1.rotation, Quaternion.Euler(0, g_AngleP1, 0), 10 * Time.deltaTime);

        }


        //プレイヤー2
        if (Input.GetKey(KeyCode.UpArrow))
        {
            angleFlagP2 += 1;
            Player2.position += transform.forward * ((Input.GetKey("a") || Input.GetKey("d")) ? 12 : 17) * Time.deltaTime;
        }

        if (Input.GetKey(KeyCode.DownArrow))
        {
            angleFlagP2 += 5;
            Player2.position -= transform.forward * ((Input.GetKey("a") || Input.GetKey("d")) ? 12 : 17) * Time.deltaTime;
        }

        if (Input.GetKey(KeyCode.LeftArrow))
        {
            angleFlagP2 += -7;
            Player2.position -= transform.right * ((Input.GetKey("w") || Input.GetKey("s")) ? 12 : 17) * Time.deltaTime;
        }

        if (Input.GetKey(KeyCode.RightArrow))
        {
            angleFlagP2 += 3;
            Player2.position += transform.right * ((Input.GetKey("w") || Input.GetKey("s")) ? 12 : 17) * Time.deltaTime;
        }

        if (angleFlagP2 != 0)
        {

            switch (angleFlagP2)
            {
                case 1:
                    g_AngleP2 = 0.0f;
                    break;
                case 3:
                    g_AngleP2 = 90.0f;
                    break;
                case 5:
                    g_AngleP2 = 180.0f;
                    break;
                case -7:
                    g_AngleP2 = -90.0f;
                    break;
                case 4:
                    g_AngleP2 = 45.0f;
                    break;
                case 8:
                    g_AngleP2 = 135.0f;
                    break;
                case -2:
                    g_AngleP2 = -135.0f;
                    break;
                case -6:
                    g_AngleP2 = -45.0f;
                    break;
                default:
                    break;
            }

            Player2.rotation = Quaternion.Slerp(Player2.rotation, Quaternion.Euler(0, g_AngleP2, 0), 10 * Time.deltaTime);

        }

    }
}
