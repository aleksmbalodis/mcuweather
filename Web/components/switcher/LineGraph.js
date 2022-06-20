import {
    Chart as ChartJS,
    CategoryScale,
    LinearScale,
    PointElement,
    LineElement,
    Title,
    Tooltip,
    Legend,
    Filler,
    TimeScale,
    TimeSeriesScale
} from "chart.js"

ChartJS.register(
    CategoryScale,
    LinearScale,
    PointElement,
    LineElement,
    Filler,
    Title,
    Tooltip,
    Legend,
    TimeSeriesScale
)
import { Line } from "react-chartjs-2"



export default function LineGraph({data, title}) {

    const options = {
        color: "black",
        scales:     {
            xAxes: [{
                type:       "time",
                time:       {
                    format: "",
                    tooltipFormat: 'll'
                },
                color: "#F2EFEA",
                scaleLabel: {
                    display:     false,
                    labelString: 'Date'
                }
            }],
            yAxes: [{
                scaleLabel: {
                    display:     true,
                    labelString: 'value'
                }
            }]
        },
        responsive: true,
        plugins: {
          legend: {
            display: true,
          },
          title: {
            display: true,
            text: title,
          },
        },
      };

    //   console.log(data)
    return (
        <Line data={data} width={100} height={40} options={options}></Line>
    )
}