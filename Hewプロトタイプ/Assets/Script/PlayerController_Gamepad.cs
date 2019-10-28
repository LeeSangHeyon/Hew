using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController_Gamepad : MonoBehaviour
{
    Transform Player1;
    Transform Player1_bow;
    Transform Player1_point;
    int bow_count;
    public GameObject Arrow;
    // Start is called before the first frame update
    void Start()
    {
        Player1 = GameObject.Find("Player1").transform;
        Player1_bow = GameObject.Find("Player1/Bow").transform;
        Player1_point = GameObject.Find("Player1/Point").transform;
        bow_count = 0;
    }

    // Update is called once per frame
    void Update()
    {

        //移動
        float TX = Input.GetAxisRaw("Horizontal1");     //Lスティック水平方向
        float TZ = Input.GetAxisRaw("Vertical1");       //Lスティック垂直方向

        if (Mathf.Abs(TX) > 0.5f || Mathf.Abs(TZ) > 0.5f)
        {
            Player1.position += new Vector3(TX,0,TZ) * 16 * Time.deltaTime;
        }

        //回り
        float RX = Input.GetAxisRaw("Horizontal2");     //Rスティック水平方向
        float RZ = Input.GetAxisRaw("Vertical2");       //Rスティック垂直方向


        if (Mathf.Abs(RX) > 0.5f || Mathf.Abs(RZ) > 0.5f)
        {
            float Angle = Mathf.Atan2(RZ, RX) * Mathf.Rad2Deg + 90.0f;
            Player1.rotation = Quaternion.Slerp(Player1.rotation, Quaternion.Euler(0, Angle, 0), 8 * Time.deltaTime);
            Player1_bow.rotation = Quaternion.Slerp(Player1_bow.rotation, Quaternion.Euler(0, Angle, 0), 8 * Time.deltaTime);
        }
        else if(Mathf.Abs(TX) > 0.5f || Mathf.Abs(TZ) > 0.5f)
        {
            float Angle = Mathf.Atan2(TX, TZ) * Mathf.Rad2Deg;
            Player1.rotation = Quaternion.Slerp(Player1.rotation, Quaternion.Euler(0, Angle, 0), 8 * Time.deltaTime);
            bow_count++;
            bow_count %= 30;
            Player1_bow.rotation = Quaternion.Slerp(Player1_bow.rotation, Quaternion.Euler(bow_count < 15 ? -45.0f : 45.0f, Angle, 0),  2 * Time.deltaTime);
        }

        //攻撃
        if (Input.GetButtonDown("FireR"))
        {
            GameObject.Find("Player1/Line").GetComponent<MeshRenderer>().enabled = true;
        }

        if (Input.GetButtonUp("FireR"))
        {
            GameObject.Find("Player1/Line").GetComponent<MeshRenderer>().enabled = false;
            GameObject Ar = Instantiate(Arrow, Player1_point.position, Player1.rotation) as GameObject;
            Rigidbody ArRb = Ar.GetComponent<Rigidbody>();
            ArRb.AddForce(new Vector3 (Mathf.Sin(Mathf.PI * Player1.localEulerAngles.y / 180.0f), 0, 
                Mathf.Cos(Mathf.PI * Player1.localEulerAngles.y / 180.0f)) * 400);

            Destroy(Ar, 1.5f);

        }

    }
}
