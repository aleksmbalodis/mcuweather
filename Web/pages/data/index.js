import useSWR from 'swr'
import React, { useState, useEffect } from 'react'
import Form from "../../components/forms";
import Table from "../../components/tables/table";
import styles from "../../styles/Data.module.css"
import Filter from '../../components/filter';
import { getData } from '../../components/api/data';
import Loading from '../../components/loading';



export default function Data() {

    //Stores data and function to change data
    const [data, setData] = useState([]); 
    //Stores loading state and function to change state
    const [loading, setLoading] = useState(true) //
    //Stores filter from date
    const [from, setFrom] = useState('')
    //Stores filter to date
    const [to, setTo] = useState('')
    const [error, setError] = useState('')


    console.log(data)
    

    useEffect(() => {
        setLoading(true)
        //Sends request to RestAPI 
        //Result populates data variable
        fetch('api/data')
            .then((res) => res.json())
            .then((result) => {
                setLoading(false);
                setData(result)
            })
    },[])

    const filter = (e) => { ///TODO: add present filter
        e.preventDefault()
        //checks if filter values are valid
        if (from && to) { 
            //filters when filter button is pressed and when date is present
            setLoading(true)
            fetch(`api/data/${from}/${to}`)
            .then((res) => res.json())
            .then((result) => {
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
                setLoading(false)
                setData(result)
            } )
        }
    }

    return (
        <div className={styles.page}>
            {/* Temporary form for testing */}
            {/* <Form></Form> */}
            <h1>Data</h1>
            {/* Filter element which controls data showed */}
            <Filter setFrom={setFrom} setTo={setTo} filter={filter} styles={styles}></Filter>
            { loading ? <Loading/> :
                <Table content={data} styles={styles}>
                    <tr className={styles.title}>
                        <th>Date</th>
                        <th>Temperature</th>
                        <th>Humidity</th>
                        <th>Brightness</th>
                    </tr></Table>}
            
        </div>
    )
}
