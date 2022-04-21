


export default function Filter({ filter, setFrom, setTo, styles }) {


    return (
        <form onSubmit={filter} className={styles.filter}>
                <label htmlFor="date-from">From:</label>
                <input name="date-from" type="datetime-local" onChange={(e) => {
                        setFrom(e.target.value)
                        // console.log(from)
                        // data = fetchData(filter)
                }}></input>
                <label htmlFor="date-to">To:</label>
                <input name="date-to" type="datetime-local" onChange={(e) => {
                        setTo(e.target.value)
                        // console.log(to)
                        // data = fetchData(filter)
                }}></input>
                <button type='submit' id="submit">Filter</button>
            </form>
    )
}