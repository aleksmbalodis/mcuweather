import styles from "../../styles/Graphs.module.css"
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


import { Line } from "react-chartjs-2"
import Switcher from "../../components/switcher"


export default function Graphs({ children, home }) {

    const labels = ['January', 'February', 'March', 'April', 'May', 'June', 'July']

    const data = {
        labels,
        datasets: [
            {
                data: [0.1, 0.4, 0.2, 0.3, 0.7, 0.4, 0.6, 0.3],
                borderColor: 'rgb(255,0,0)',
            }
        ],
    };

    const options = {
        responsive: true,
        plugins: {
          legend: {
            display: false,
          },
          title: {
            display: true,
            text: 'Chart.js Line Chart',
          },
        },
      };

    return (

        <div className={styles.page}>
            <h1>Graphs</h1>
            <Switcher></Switcher>
            {/* <Line data={data} width={100} height={40} options={options}></Line> */}
            {/* <canvas id="myChart" width={400} height={400}></canvas> */}
        </div>
    )
}