import useSWR from 'swr'
import React, { useState, useEffect } from 'react'
import Form from "../../components/forms";
import Table from "../../components/tables/table";
import styles from "../../styles/Data.module.css"
import Filter from '../../components/filter';
import { getData } from '../../components/api/data';
// import fetchData, { getFilteredData } from '../../lib/data';
// let filter = {from:0, to:0};



export default function Data() {

    const [data, setData] = useState([]);
    const [loading, setLoading] = useState(true)
    const [from, setFrom] = useState('')
    const [to, setTo] = useState('')
    const [error, setError] = useState('')

    
    // let {data, error } = fetchData()
    console.log(data)
    

    useEffect(() => {
        setLoading(true)
        setData(getData())
        // fetch('api/data')
        //     .then((res) => res.json())
        //     .then((result) => {
        //         setLoading(false);
        //         // console.log(result)
        //         setData(result)
        //     })
    },[])

    const filter = (e) => { ///TODO: add present filter
        e.preventDefault()
        if (from && to) { //filters when filter button is pressed and when date is present
            setLoading(true)
            setData(getData(from,to))
            // fetch(`api/data/${from}/${to}`)
            // .then((res) => res.json())
            // .then((result) => {
            //     // console.log(result)
            //     setLoading(false)
            //     setData(result)
            // } )
        }
        else { // filters when fulterbutton is pressed but dates are cleared
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




    // const options = {
    //     body: {},
    //     headers: {
    //     'Content-Type': 'application/json'
    //     },
    //     method: 'POST'
    // }

    // const filter = async (event) => {

    //     const res = await fetch("/api/data/fetch", options)
    //     const result = await res.json()

    // }

    return (
        <div className="">
            <Form></Form>
            <Filter setFrom={setFrom} setTo={setTo} filter={filter}></Filter>
            {/* <form onSubmit={filter}>
                <label htmlFor="date-from">from:</label>
                <input name="date-from" type="datetime-local" onChange={(e) => {
                        setFrom(e.target.value)
                        console.log(from)
                        // data = fetchData(filter)
                }}></input>
                <label htmlFor="date-to">to:</label>
                <input name="date-to" type="datetime-local" onChange={(e) => {
                        setTo(e.target.value)
                        console.log(to)
                        // data = fetchData(filter)
                }}></input>
                <input type='submit'></input>
            </form> */}
            {
                // data ? <Table content={data} styles={styles}> </Table> : <h1>LOADING...</h1>
            }

            { loading ? <div>Loading...</div> :
                <Table content={data} styles={styles}>
                    <tr>
                        <th>Date</th>
                        <th>Temperature</th>
                        <th>Humidity</th>
                        <th>Brightness</th>
                    </tr></Table>}
            
        </div>
    )
}
