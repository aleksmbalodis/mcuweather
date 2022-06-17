import styles from "../../styles/Graphs.module.css"

import { capitalizeFirstLetter } from "../../components/Utils"

import {
    Chart as ChartJS,
    CategoryScale,
    LinearScale,
    PointElement,
    LineElement,
    Title,
    Tooltip,
    Legend,
    Filler
} from "chart.js"

ChartJS.register(
    CategoryScale,
    LinearScale,
    PointElement,
    LineElement,
    Filler,
    Title,
    Tooltip,
    Legend
)
import Filter from "../../components/filter"
import LineGraph from "../../components/switcher/LineGraph"
import React, { useState, useEffect } from 'react'
import Loading from "../../components/loading"



export default function Graphs({ home }) {

    //data variabl which stores incoming data
    const [data, setData] = useState([]);
    //Loading state which is active while loading data
    const [loading, setLoading] = useState(true)
    //Stores filter from date
    const [from, setFrom] = useState('')
    //Stores filter to date
    const [to, setTo] = useState('')
    const [error, setError] = useState('')
    //sets graphs default values
    const [graph, setGraph] = useState({graph: "humidity", color: "rgba(255,255,255,0.60)"})
    const [filtered, setFiltered] = useState([])
    // console.log(data)

    

    

    useEffect(() => {
        //Data gets requested from server using RestAPI
        fetch('api/data')
            .then((res) => res.json())
            .then((result) => {
                setLoading(false);
                // console.log(result)
                setData(result)
                
            })
    }, [])

    //testing area
    // data.forEach((x) => {
    //     console.log(x.date, "Date string")
    //     console.log(new Date(x.date).toUTCString(), "Date parse")
    // })

    
    const graphData = {
        datasets: [
            {
                //populates graphs data
                data: data.map((x) => x = { x: new Date(x.date).toUTCString(), y: x[graph.graph]} ),
                borderColor: graph.color,
                //sets color for the graph
                color: "wheat",
                //capitalizes first letter in labels
                label: capitalizeFirstLetter(graph.graph),
            }
        ],
    };

    const filter = (e) => { ///TODO: add present filter
        e.preventDefault()
        //filters when filter button is pressed and when date is present
        if (from && to) { 
            setLoading(true)
            // setData(getData(from,to))
            fetch(`api/data/${from}/${to}`)
            .then((res) => res.json())
            .then((result) => {
                // console.log(result)
                setLoading(false)
                setData(result)
            } )
        }
        else { 
            // filters when fulterbutton is pressed but dates are cleared
            setLoading(true)
            fetch(`api/data`)
            .then((res) => res.json())
            .then((result) => {
                // console.log(result)
                setLoading(false)
                setData(result)
            } )
        }
    }
    
    return (

        <div className={styles.page}>
            <h1>Graphs</h1>
            <Filter setFrom={setFrom} setTo={setTo} filter={filter} styles={styles}></Filter>            
            <ul>
                <li><a onClick={(e) => {setGraph({graph:"brightness", color: "darkcyan", bgcolor:"#F2EFEA"})}} className={styles.brightness}>Brightness</a></li>
                <li><a onClick={(e) => {setGraph({graph:"humidity", color: "darkgoldenrod", bgcolor:"#dad7d4"})}} className={styles.humidity}>Humidity</a></li>
                <li><a onClick={(e) => {setGraph({graph:"temperature", color: "firebrick" , bgcolor:"#c5c2c0"})}} className={styles.temperature}>Temperature</a></li>
            </ul>
            {/* changes background color of graphs depending on selected graph */}
            <div className={styles.content} style={{ backgroundColor: graph.bgcolor}}>
                {/* replaces data with loading while data isnt loaded. */}
                {loading ? <Loading/> : <LineGraph title={capitalizeFirstLetter(graph.graph)} className={styles.graph} data={graphData}></LineGraph>
                }
                
            </div>
            {/* <Line data={data} width={100} height={40} options={options}></Line> */}
            {/* <canvas id="myChart" width={400} height={400}></canvas> */}
        </div>
    )
}



