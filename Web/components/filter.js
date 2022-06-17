


export default function Filter({ filter, setFrom, setTo, styles }) {


    return (
        <form onSubmit={filter} className={styles.filter}>
                <label htmlFor="date-from">From:</label>
                <input name="date-from" type="datetime-local" onChange={(e) => {
                        //Sets Starting value of filter
                        setFrom(e.target.value) 
                }}></input>
                <label htmlFor="date-to">To:</label>
                <input name="date-to" type="datetime-local" onChange={(e) => {
                        //Sets ending value of filter
                        setTo(e.target.value) 
                }}></input>
                <button type='submit' id="submit">Filter</button>
            </form>
    )
}