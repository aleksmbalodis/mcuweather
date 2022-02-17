import React, {useState, useEffect} from 'react'

module.exports = getWeather = () => {
    return fetch(`api/weather`, {
        headers: {
          'Content-Type': 'application/json',
          'Accept': 'application/json'
        }
      }).then((response) => response.json())
}