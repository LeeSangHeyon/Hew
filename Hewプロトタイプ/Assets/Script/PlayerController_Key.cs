using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController_Key : MonoBehaviour
{
    Transform Player2;
    Transform Player2_sword;
    float g_AngleP2;
    int sword_count;

    // Start is called before the first frame update
    void Start()
    {
  
        Player2 = GameObject.Find("Player2").transform;
        Player2_sword = GameObject.Find("Player2/SwordA").transform;

        g_AngleP2 = 0.0f;
        sword_count = 0;
    }

    // Update is called once per frame
    void Update()
    {

        int angleFlagP2 = 0; 



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


        if (Input.GetKey(KeyCode.Z))
        {
            sword_count++;
            sword_count %= 20;
            Player2_sword.rotation = Quaternion.Slerp(Player2_sword.rotation, Quaternion.Euler(sword_count < 10 ? 170.0f : 10.0f,
               Player2.eulerAngles.y, 0), 10 * Time.deltaTime);
        }
        else
        {
            sword_count = 0;
            Player2_sword.rotation = Player2.rotation;
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
