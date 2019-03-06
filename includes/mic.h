/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mic.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadawson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 17:45:14 by jadawson          #+#    #+#             */
/*   Updated: 2019/03/05 19:24:35 by jadawson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MIC_H
# define MIC_H
# include <pocketsphinx.h>
# include <sphinxbase/ad.h>
# include <sphinxbase/err.h>

const char *recognize_from_microphone();
#endif
