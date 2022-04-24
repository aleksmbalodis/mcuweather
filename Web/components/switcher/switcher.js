import styles from "../../styles/Switcher.module.css"
import LineGraph from "./LineGraph"
import React, { useState, useEffect } from 'react'
import Filter from "../filter"

export default function Switcher({graphs, children, data}) {

    
    // const [data, setData] = useState()
    const labels = ['January', 'February', 'March', 'April', 'May', 'June', 'July']

    const data = {
        labels,
        datasets: [
            {
                data: [0.1, 0.4, 0.2, 0.3, 0.7, 0.4, 0.6, 0.3],
                borderColor: 'rgb(255,0,0)',
                label: "Sex",
            }
        ],
    };

    return (
        <div className={styles.page}>
            
        </div>
    )
}