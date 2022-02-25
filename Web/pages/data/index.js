import useSWR from 'swr'

import Form from "../../components/forms";
import Table from "../../components/tables/table";
import styles from "../../styles/Data.module.css"
import fetchData from '../../lib/data';
let filter = {from:0, to:0};



export default function Data({ children, props}) {


    
    let {data, error } = fetchData()
    console.log(error)
    





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
            <form>
                <label htmlFor="date-from">from:</label>
                <input name="date-from" type="datetime-local" onChange={(e) => {
                        filter.from = e.target.value
                        console.log(filter)
                        data = fetchData(filter)
                }}></input>
                <label htmlFor="date-to">to:</label>
                <input name="date-to" type="datetime-local" onChange={(e) => {
                        filter.to = e.target.value
                        console.log(filter)
                        data = fetchData(filter)
                }}></input>
            </form>
            {
                data ? <Table content={data} styles={styles}> </Table> : <h1>LOADING...</h1>
            }
            
        </div>
    )
}
