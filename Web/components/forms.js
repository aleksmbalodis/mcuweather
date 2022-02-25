
import styles from "../styles/Form.module.css"

export default function Form({ children }) {

    const uploadData = async event => {
        event.preventDefault()

        const res = await fetch('/api/data/upload', {
            body: JSON.stringify({
            Token: "",
            data:{
                date: event.target.date.value,
                temperature: event.target.temperature.value,
                humidity: event.target.humidity.value,
                brightness: event.target.brightness.value,
            }
              
            }),
            headers: {
              'Content-Type': 'application/json'
            },
            method: 'POST'
          })
      
          const result = await res.json()
    }

    return (
        <form onSubmit={uploadData} className={styles.form}>
            <label htmlFor="date">Date</label>
            <input id="date" type="datetime-local" required/>
            <label htmlFor="temperature">Temparature</label>
            <input id="temperature" type="number" required/>
            <label htmlFor="humidity">humidity</label>
            <input id="humidity" type="number" required/>
            <label htmlFor="brightness">brightness</label>
            <input id="brightness" type="number" required/>
            <button type="submit">Add data</button>
        </form>
    )
}